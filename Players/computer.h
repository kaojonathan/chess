#ifndef COMPUTER_H_
#define COMPUTER_H_
#include <vector>
// abstract class for the different AI levels
#include "player.h"

class Piece;
class Board;

class Computer : public Player {
        int level;
        virtual void move() = 0;
    public:
        Computer(int side, int level);
        virtual ~Computer();
        // asks computer player to make a move
        int playerMove(int, int, int, int) override { 
            move();
            return 1;
        }
};

#endif
