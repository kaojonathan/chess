#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>

class Piece;
class Board;

class Player {
    protected:
        int side; // 0 for white and 1 for black
        Board* gameBoard;
        // the player's pieces
        std::vector<Piece*> pieces; 
        // the opponent's pieces
        std::vector<Piece*> enemypieces;
        int type; // 0 for human, 1 for computer 
        virtual int playerMove(int oldCol, int oldRow, int newCol, int newRow) = 0;

    public:
        Player(int side, int type);
        virtual ~Player();
        int move(int oldCol, int oldRow, int newCol, int newRow) { 
            return playerMove(oldCol, oldRow, newCol, newRow);
        }
        int getType() {
            return type;
        }
};



#endif