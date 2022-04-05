#ifndef PIECE_H_
#define PIECE_H_
#include <utility>
#include <string>
#include <vector>

class Board;
class Player;

class Piece {
    protected:
    ///// fields: /////
        int x;                                              // col
        int y;                                              // row
        int side;                                           // 0 for white and 1 for black
        int value;                                          // the value of the Piece
        int updateStatus;                                   // 0: not update, 1: normal update, 2: forced update
        bool recent;                                        // moved recently
        std::vector<std::pair<int,int>> moves;              // moves contains vector of valid move position
        std::vector<std::pair<int,int>> targets;            // a list of position of enemy that the piece can capture.
        std::vector<std::pair<int,int>> protects;           // a list of position of allies that the piece protects 
        std::vector<std::pair<int,int>> castle;             // a list of valid castle move
        Piece * forced;                                     // the piece that cause this cannot move
        std::vector<std::pair<int,int>> checkRoute;         // the path that can be block
        int numMoves;                                       // number of move
        std::string representation;                         // representation of a piece
        Board* gameBoard;                                   // the two players board
        Player* opponent;                                   // opponent player

    ///// virtual functions: /////
        // updates possible moves and attack targets, not consider if the piece is forced or not
        virtual void nUpdate() = 0;
        // updates possible moves and attack targets for a forced Piece
        virtual void fUpdate(Piece*);
        // for computer level 2/3 class
        // return a list of Piece that the piece can attack if it is in position at
        virtual std::vector<Piece *> attackable(std::pair<int, int> at) = 0;
         // return false if the position is the not valid one the piece can go
        bool validPos(std::pair<int,int>);
    
    public:
    ///// Public methods /////
        // constructor and destructor
        Piece(int side, int x, int y, Board *);
        virtual ~Piece();
        // getters of fields
        int getX();
        int getY();
        int getSide();
        bool getRecent();
        int getVal();
        std::string getRep();
        std::vector<std::pair<int,int>> getMoves();
        std::vector<std::pair<int,int>> getTargets();
        std::vector<std::pair<int,int>> getProtects();
        std::vector<std::pair<int, int>> getCheckRoute();
        int getNumMoves();
        // setters of fields:
        // set recent to true
        void setRecent();
        // set recent to false
        void resetRecent();
        
        // set x and y
        void setPos(int col, int row);  // make sure col first and row second
        // set updateStatus to 0; set moves, targets, protects, castle and checkRoute to empty
        void needsUpdate();
        // set gameBoard
        void attach(Board* board);
        // determine if the Piece can move to position (x,y), 0: no, 1: move, 2: capture
        int move(int col, int row);
        // set the opponent player of the piece
        void setOpponent(Player *);

        //  Scan the each direction base on type, return a list of attackable enemies, if any
        //  type = 1: diagonal; 2: horizontal/vertical; 3: both diagonal and horizontal/vertical
        std::vector<Piece *> dScan(std::pair<int,int>, int type);
        //  update moves, attacks and check route base on type (can be used by Bishop, Queen and Rook only)
        //  type = 1: diagonal; 2: horizontal/vertical; 3: both diagonal and horizontal/vertical
        void dirScan(int type);
        //  true if the target is a king
        bool isKing();
        //  true if the target is the enemy king
        bool enemyKing(Piece * target);
         // determines if the piece in position (col, row) checks the king,
        bool posInCheck(int col, int row);
        // return true if this Piece can attack the enemy piece in position (col, row) (regardness the existence of the piece)
        // note that this can be use to determine a position is controled by the enemy
        bool canAttack(std::pair<int, int>);
        // return the update status
        bool isUpdated();
        // for Pieces that is not king, set the forced field into the given pieces, for King, update the excape route of the king.
        void forcedBy(Piece *, bool check = false);
        // update moves and targets field, notify any enemy piece when forcing it, or notify the opponent when this piece is checking the king.
        void statusUpdate();
        // number of move ++
        void incNumMoves();
        // public method for attackable()
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