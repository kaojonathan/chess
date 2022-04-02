#ifndef FOUR_H_
#define FOUR_H_
#include "computer.h"

class Piece;
class Board;

class Four : public Computer {

	std::pair<int, std::string> move(int &oldCol, int &oldRow, int &newCol, int &newRow) override;
public:
	Four(int side, int level);
};



#endif