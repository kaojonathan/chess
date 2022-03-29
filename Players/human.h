// DO NOT MODIFY THIS FILE
#ifndef HUMAN_H_
#define HUMAN_H_
#include <vector>
// abstract class for the different AI levels
#include "player.h"

class Piece;
class Board;

class Human : public Player {
    int playerMove() override;
    public:
        Human(int);
        
};

#endif


