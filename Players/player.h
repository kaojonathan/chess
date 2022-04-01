#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <utility>

class Piece;
class Board;

class Player {
    protected:
        int side; // 0 for white and 1 for black
        Board* gameBoard;
        Piece * king;            // may change type to King
        // PLAYER OWNS THE PIECES
        // the player's pieces
        std::vector<Piece*> pieces; 
        // the pieces not on the board
        std::vector<Piece*> inactivePieces; 
        // the opponent
        Player *opponent;
        Piece *opponentCheck;
        int type; // 0 for human, 1 for computer 
        virtual int playerMove(int oldCol, int oldRow, int newCol, int newRow) = 0;

    public:
        Player(int side, int type);
        virtual ~Player();
        void init(Board *);
        void claimPieces();
        int move(int oldCol, int oldRow, int newCol, int newRow) { 
            return playerMove(oldCol, oldRow, newCol, newRow);
        }
        void print();
        int getType() {
            return type;
        }
        std::vector<Piece*> getPieces() {
            return pieces;
        }

        void removePiece(std::pair<int,int>); // removes the piece in position (x, y) and places it in inactivePieces.

        // list all the Pieces that can attack the given position
        std::vector<Piece*> canAttack(std::pair<int, int>);

        // set opponentCheck to the Piece 
        void kingCheckedBy(Piece *);

        // update all the status fields of each piece
        int checkStatus();
        // unset the status fields of each piece
        void unsetStatus();
        // true if the player still has valid move
        bool canMove();
};



#endif