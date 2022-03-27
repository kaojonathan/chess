#ifndef PIECE_H_
#define PIECE_H_
#include <utility>
#include <string>
#include <vector>

class Board;

class Piece {
    protected:
        int x;
        int y;
        int side; // 0 for white and 1 for black
        int value;  // the value of the Piece
        std::vector<std::pair<int,int>> moves;            // contains possible move, update after a Player::move
        std::vector<std::pair<int,int>> attacks;           // contains a list of pos that the piece can capture pieces on such location.
        Piece * forced;                  // the piece that cause this cannot move
        std::vector<std::pair<int,int>> checkRoute;       // the path that can be block
        std::string representation;
        Board* gameBoard;
        // determine if the Piece can move to position (x,y), 0: no, 1: move, 2: capture
        virtual int canMove(int x, int y);
        // updates possible moves
        virtual void updateMovePossibilities() = 0; 
        // if the piece is checking the king
        virtual bool kingInCheck();

        // added this (vincent) /// for computer level 2/3 class

        // returns the coordinate (x, y) that the piece can move to, 
        // to check the king, or (-1, -1) if no move is found
        virtual std::pair<int, int> getCheckCoords() = 0; 
        // determines if the piece in position (x, y) checks the king,
        virtual bool posInCheck(int x, int y) = 0;
        virtual void forcedBy(Piece *);

    public:
        Piece(bool isWhite);
        void setPos(int row, int col);
        void attach(Board* board);
        // attempts to move a piece
        int move(int x, int y) {
            return canMove(x,y);
        }
        bool kingCheck(bool isWhite) {
            return kingInCheck();
        }
        bool isKing(); // true if is king
        int getX();
        int getY();
        int getSide();
        std::string getRep();
        void updateMoves() {
            updateMovePossibilities();
        }
        std::vector<std::pair<int, int>> getCheckRoute();

        int getVal();                   // return the value of a piece
        
        // the following: type = 1: diagonal; 2: horizontal/vertical; 3: both diagonal and horizontal/vertical
        //  Scan the each direction, return the most valuable emeny piece, if any
        Piece * dScan(int x, int y, int type);
        //  update moves, attacks and check route base on type (can be used by Bishop, Queen and Rook only)
        void updateStatus(int type);    
};
   


#endif