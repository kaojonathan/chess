#ifndef PIECE_H_
#define PIECE_H_
#include <utility>
#include <string>
#include <vector>

class Board;
class Player;

class Piece {
    protected:
        // need to decide if x is a column or a row, now x is col
        int x;
        int y;
        int side; // 0 for white and 1 for black
        int value;  // the value of the Piece
        std::vector<std::pair<int,int>> moves;              // contains possible move, update after a Player::move
        std::vector<std::pair<int,int>> attacks;            // contains a list of position that the piece can capture pieces on such location.
        Piece * forced;                                     // the piece that cause this cannot move
        std::vector<std::pair<int,int>> checkRoute;         // the path that can be block
        std::string representation;
        Board* gameBoard;
        Player* enemy;
        // updates possible moves
        virtual void updateMovePossibilities() = 0;

        // added this (vincent) /// for computer level 2/3 class

        // returns the coordinate (x, y) that the piece can move to, 
        // to check the king, or (-1, -1) if no move is found
        // edit: may no more be useful

        /* virtual std::pair<int, int> getCheckCoords() = 0; */


        // determines if the piece in position (col, row) checks the king,
        virtual bool posInCheck(int col, int row) = 0;
        // make this piece forced by a piece
        virtual void forcedBy(Piece *);
        // return true if this Piece can attack the enemy piece in position (col, row) (regardness the existence of the piece)
        virtual bool canAttack(int col, int row);

    public:
        Piece(bool isWhite);
        int getX();
        int getY();
        int getSide();
        void setPos(int col, int row);  // make sure row first or column first
        void attach(Board* board);
        // determine if the Piece can move to position (x,y), 0: no, 1: move, 2: capture
        int move(int col, int row);
        // true if the piece is checking the king
        bool kingCheck();
        std::string getRep();   // print the representation
        void updateMoves();

        // return the checkRoute field
        std::vector<std::pair<int, int>> getCheckRoute();

        int getVal();                   // return the value of a piece
        
        // the following: type = 1: diagonal; 2: horizontal/vertical; 3: both diagonal and horizontal/vertical
        //  Scan the each direction, return the most valuable emeny piece, if any
        Piece * dScan(int x, int y, int type);
        //  update moves, attacks and check route base on type (can be used by Bishop, Queen and Rook only)
        void updateStatus(int type);
        bool isKing();
        bool EnemyKing(Piece * target);   // the piece is the true if the target is the enemy king
};
   


#endif