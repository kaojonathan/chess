#ifndef COMPUTER_H_
#define COMPUTER_H_
#include <vector>
#include <iostream>
// abstract class for the different AI levels
#include "player.h"

class Piece;
class Board;

class Computer : public Player {
        int level;
        virtual std::pair<int, std::string> move(int &oldCol, int &oldRow, int &newCol, int &newRow) = 0;
    public:
        Computer(int side, int level);
        virtual ~Computer();
        // asks computer player to make a move
        /*
# return 0 if ask for different move (move failed) (NEVER GONNA HAPPEN)
# return 1 if move was successful (ask for next move)
# return 2 if capture was sucessful (ask for next move)
*/
        std::pair<int, std::string> playerMove(int &oldCol, int &oldRow, int &newCol, int &newRow) override { 
return move(oldCol, oldRow, newCol, newRow);
        }
};

#endif
