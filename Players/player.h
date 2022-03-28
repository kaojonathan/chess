#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>

class Piece;
class Board;
class Player {
    protected:
        int side; // 0 for white and 1 for black
        Board* gameBoard;
        std::vector<Piece*> pieces; // the human's pieces
        std::vector<Piece*> enemypieces; // the opponent's pieces





};



#endif