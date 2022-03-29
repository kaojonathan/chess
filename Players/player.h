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
        // the pieces captured from opponent
        std::vector<Piece*> enemypieces;
        int type; // 0 for human, 1 for computer 
        int virtual playerMove() = 0;

    public:
        Player(int side, int type);
        virtual ~Player();
        int move() { 
            return playerMove();
        }
        int getType() {
            return type;
        }
};



#endif