#ifndef PIECE_H_
#define PIECE_H_
#include <utility>
#include <string>
#include <vector>

class Board;
class Player;

class Piece {
    protected:

        std::vector<std::pair<int,int>> castle;



        // need to decide if x is a column or a row, now x is col
        int x;
        int y;
        int side; // 0 for white and 1 for black
        int value;  // the value of the Piece
        int updateStatus; // 0: not update, 1: normal update, 2: forced update

        bool recent; // moved recently

        std::vector<std::pair<int,int>> moves;              // moves contains vector of valid move position
        std::vector<std::pair<int,int>> targets;            // contains a list of position of enemy that the piece can capture.
        // std::vector<std::pair<int,int>> protects;           // position of allies it is currently protecting
        Piece * forced;                                     // the piece that cause this cannot move
        std::vector<std::pair<int,int>> checkRoute;         // the path that can be block
        int numMoves;                                       // can't think of a name yet, but different in each type pieces. for castle, en passant etc.
        std::string representation;
        Board* gameBoard;
        Player* opponent;
        // updates possible moves and attack targets, not consider if the piece is forced or not
        virtual void nUpdate() = 0;

        // updates possible moves and attack targets for a forced Piece
        virtual void fUpdate(Piece*);

        // added this (vincent) /// for computer level 2/3 class

        // returns the coordinate (x, y) that the piece can move to, 
        // to check the king, or (-1, -1) if no move is found
        // edit: may no more be useful

        /* virtual std::pair<int, int> getCheckCoords() = 0; */

        // return all attackable enemy piece if the piece is pos
        virtual std::vector<Piece *> attackable(std::pair<int, int> at) = 0;

         // return false if the position is the not valid one the piece can go
        bool validPos(std::pair<int,int>);

        virtual void unsetStatus();


    public:
        Piece(int side, int x, int y, Board *);
        virtual ~Piece();
        int getX();
        int getY();
        int getSide();
        void setRecent();
        void resetRecent();
        bool getRecent();
        std::vector<std::pair<int,int>> getMoves();
        std::vector<std::pair<int,int>> getTargets();
        void setPos(int col, int row);  // make sure col first and row second
        void needsUpdate();
        void attach(Board* board);
        // determine if the Piece can move to position (x,y), 0: no, 1: move, 2: capture
        int move(int col, int row);
        // true if the piece is checking the king  still use it?
        // bool kingCheck();

        std::vector<std::pair<int, int>> getCheckRoute(); // return the checkRoute field
        int getVal();                   // return the value of a piece
        std::string getRep();           // return the representation
        // following: type = 1: diagonal; 2: horizontal/vertical; 3: both diagonal and horizontal/vertical
        //  Scan the each direction, return a list of attackable enemies, if any
        std::vector<Piece *> dScan(std::pair<int,int>, int type);

        //  update moves, attacks and check route base on type (can be used by Bishop, Queen and Rook only)
        void dirScan(int type);

        bool isKing();                      //  true if the target is a king
        bool enemyKing(Piece * target);     //  true if the target is the enemy king

         // determines if the piece in position (col, row) checks the king,
        bool posInCheck(int col, int row);

                // return true if this Piece can attack the enemy piece in position (col, row) (regardness the existence of the piece)
        // note that this can be use to determine a position is controled by the enemy
        bool canAttack(std::pair<int, int>);
        // return true if this piece can attack the enemy piece in position (col, row)
        // may be useful

        bool isUpdated();
        
        // for Pieces that is not king, set the forced field into the given pieces, for King, update the excape route of the king.
        void forcedBy(Piece *, bool check = false);
        // update moves and targets field, notify any enemy piece when forcing it, or notify the opponent when this piece is checking the king.
        void statusUpdate();

        // set the opponent player of the piece
        void setOpponent(Player *);

        int getNumMoves();
        void incNumMoves(); // ++numMoves

        
        std::vector<Piece *> getAttackable(std::pair<int, int> at) {
    return attackable(at);
}


};
   
// get the most valuable Piece
Piece * mostVal(std::vector<Piece *>);

// generate the paths with direction based on type: 
//	1: diagonal directions only
//	2: cross directions only
//	3: both diagonal and cross directions
std::vector<std::pair<int, int>> getPos(int col, int row, int i, int type);



#endif