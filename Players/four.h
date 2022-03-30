#ifndef FOUR_H_
#define FOUR_H_
#include "computer.h"

class Piece;
class Board;

class Four : public Computer {

	void move() override;
public:
	Four(int side, int level);
};



#endif