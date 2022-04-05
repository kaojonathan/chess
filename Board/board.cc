#include "board.h"

Board::Board() {} // constructor

Board::~Board() {} // destructor

bool Board::checkPos(int x, int y) { return validPos(x, y); } // checks if the position at (x, y) is valid
