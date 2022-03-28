// DO NOT MODIFY THIS FILE
#ifndef HUMAN_H_
#define HUMAN_H_
#include <vector>
// abstract class for the different AI levels
#include "player.h"

class Piece;
class Board;

class Human : public Player {
    protected:
        int side; // 0 for white and 1 for black
        Board* gameBoard;
        std::vector<Piece*> pieces; // the human's pieces
        std::vector<Piece*> enemypieces; // the opponent's pieces

        virtual void move() = 0;
        
    public:
        Human(int);
        virtual ~Human(); // needs implementation
        // asks computer player to make a move
        void humanMove() { 
            move();
        }
};

#endif


