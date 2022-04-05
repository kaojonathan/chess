// DO NOT MODIFY THIS FILE
#ifndef HUMAN_H_
#define HUMAN_H_
#include <vector>
// abstract class for the different AI levels
#include "player.h"

class Piece;
class Board;

class Human : public Player
{
    // moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
    // returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
    std::pair<int, std::string> playerMove(int &oldCol, int &oldRow, int &newCol, int &newRow) override;
public:
    // constructor
    Human(int);
};

#endif
