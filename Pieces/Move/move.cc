#include <string>
#include "move.h"
using namespace std;
string Move::getType()
{
    return type;
}
int Move::getPos1x()
{
    return pos1x;
}
int Move::getPos1y()
{
    return pos1y;
}
int Move::getPos2x()
{
    return pos2x;
}
int Move::getPos2y()
{
    return pos2y;
}

Move::~Move() {}


Move::Move(int x1, int y1, int x2, int y2, std::string type): pos1x{x1}, pos1y{y1}, pos2x{x2}, pos2y{y2}, type{type} {}