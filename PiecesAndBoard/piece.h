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
        std::vector<std::pair<std::pair<int,int>, vector<Piece *>>> moves; // moves contains vector of pair(valid move position, vectors of attackable emeny pieces)
        std::vector<std::pair<int,int>> attacks;            // contains a list of position that the piece can capture pieces on such location.
        std::vector<Piece *> guarded;                        // protected by these pieces (not implemented yet)
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

        // return all attackable enemy piece if the piece is pos
        virtual std::vector<Piece *> attackable(std::pair<int, int> at) = 0;

        // make this piece forced by a piece
        virtual void forcedBy(Piece *);


        // return true if this Piece can attack the enemy piece in position (col, row) (regardness the existence of the piece)
        // note that this can be use to determine a position is controled by the enemy
        virtual bool canAttack(std::pair<int, int>);
        // return true if this piece can attack the enemy piece in position (col, row) if it is at pos
        // may be useful
        // virtual bool canAttack(int col, int row, std::pair<int,int> pos) = 0;

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
        
        // following: type = 1: diagonal; 2: horizontal/vertical; 3: both diagonal and horizontal/vertical
        //  Scan the each direction, return a list of attackable enemies, if any
        vector<Piece *> dScan(std::pair<int,int>, int type);

        //  update moves, attacks and check route base on type (can be used by Bishop, Queen and Rook only)
        void updateStatus(int type);

        bool isKing();                      //  true if the target is a king
        bool enemyKing(Piece * target);     //  true if the target is the enemy king

         // determines if the piece in position (col, row) checks the king,
        bool posInCheck(int col, int row);
};
   
// get the most valuable Piece
Piece * mostVal(std::vector<Piece *>);

// generate the paths with direction based on type: 
//	1: diagonal directions only
//	2: cross directions only
//	3: both diagonal and cross directions
std::vector<std::pair<int, int>> getPos(int col, int row, int i, int type);

#endif