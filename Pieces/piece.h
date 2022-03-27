#ifndef PIECE_H_
#define PIECE_H_
#include <string>
#include <vector>

class Board;

class Piece {
    protected:
        int x;
        int y;
        int side; // 0 for white and 1 for black
        vector<int[2]> moves;            // contains possible move, update after a Player::move
        vector<int[2]> attacks;           // contains a list of pos that the piece can capture pieces on such location.
        Piece * forced;                  // the piece that cause this cannot move
        vector<int[2]> checkRoute;       // the path that can be block
        std::string representation;
        Board* gameBoard;
        // determine if the Piece can move to position (x,y), 0: no, 1: move, 2: capture
        virtual int canMove(int x, int y) = 0;
        // updates possible moves
        virtual void updateMovePossibilities() = 0; 
        // if the piece is checking the king
        virtual bool kingInCheck(bool isWhite) = 0;

        // added this (vincent) /// for computer level 2/3 class

        // returns the coordinate (x, y) that the piece can move to, 
        // to check the king, or (-1, -1) if no move is found
        virtual std::pair<int, int> getCheckCoords() = 0; 
        // determines of the piece in position (x, y) checks the king,
        virtual bool posInCheck(int x, int y) = 0;

        virtual bool isKing(); // true if is king
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
            return kingInCheck(isWhite);
        }
        int getX();
        int getY();
        int getSide();
        std::string getRep();
        void updateMoves() {
            updateMovePossibilities();
        }
        vector<int[2]> getCheckRoute();
};

#endif