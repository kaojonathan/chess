#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <utility>
#include <string>
#include <memory>

class Piece;
class Board;

class Player {
    protected:
        int side; // 0 for white and 1 for black
        Board* gameBoard;
        std::unique_ptr<Piece> king;            // may change type to King
        // PLAYER OWNS THE PIECES
        // the player's pieces
        std::vector<std::unique_ptr<Piece>> pieces; 
        // the pieces not on the board
        std::vector<std::unique_ptr<Piece>> inactivePieces; 
        // the opponent
        Player *opponent;
        Piece *opponentCheck;
        int type; // 0 for human, 1 for computer 
        virtual std::pair<int, std::string> playerMove(int &oldCol, int &oldRow, int &newCol, int &newRow) = 0;

    public:
        Player(int side, int type);
        virtual ~Player();
        void init(Board *, Player *player);
        void claimPieces();
        std::pair<int, std::string> move(int &oldCol, int &oldRow, int &newCol, int &newRow) { 
            return playerMove(oldCol, oldRow, newCol, newRow);
        }
        void print();
        int getType() {
            return type;
        }
        std::vector<std::unique_ptr<Piece>> const& getPieces() {
            return pieces;
        }

        void addToPieces(Piece *p);

        void removePiece(std::pair<int,int>); // removes the piece in position (x, y) and places it in inactivePieces.

        void deletePiece(std::pair<int,int>); // deletes the piece in position (x, y) DELETE
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