#ifndef COMPUTER_H_
#define COMPUTER_H_
#include <vector>
#include <iostream>
// abstract class for the different AI levels
#include "player.h"

class Piece;
class Board;

class Computer : public Player
{ // computer is a type of player
        int level; // the level of the computer
        // moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
        // returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
        virtual std::pair<int, std::string> move(int &oldCol, int &oldRow, int &newCol, int &newRow) = 0;
public:
        // constructor
        Computer(int side, int level);
        virtual ~Computer(); // destructor
        // moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
        // returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
        std::pair<int, std::string> playerMove(int &oldCol, int &oldRow, int &newCol, int &newRow) override
        {
                return move(oldCol, oldRow, newCol, newRow);
        }
};

#endif
