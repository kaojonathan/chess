#ifndef ONE_H_
#define ONE_H_
#include "computer.h"

class One : public Computer
{	// one is a type of computer (difficulty)
	// moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
	// returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
	std::pair<int, std::string> move(int &, int &, int &, int &) override;
public:
	One(int side, int level); // constructor
};

#endif