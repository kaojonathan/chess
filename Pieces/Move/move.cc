#include <string>
#include "move.h"
using namespace std;

// gets the type of the move
string Move::getType()
{
    return type;
}

// gets the start x pos
int Move::getPos1x()
{
    return pos1x;
}

// gets the start y pos
int Move::getPos1y()
{
    return pos1y;
}

// gets the end x pos
int Move::getPos2x()
{
    return pos2x;
}

// gets the end y pos
int Move::getPos2y()
{
    return pos2y;
}

Move::~Move() {} // destructor

// constructor
Move::Move(int x1, int y1, int x2, int y2, std::string type): pos1x{x1}, pos1y{y1}, pos2x{x2}, pos2y{y2}, type{type} {}