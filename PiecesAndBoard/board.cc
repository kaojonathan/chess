#include "board.h"

Board::Board() {}

Board::~Board() {}

bool Board::checkPos(int x, int y) { return validPos(x, y); }
