#ifndef TWO_H_
#define TWO_H_
#include "computer.h"

class Two : public Computer
{ // two is a type of computer (difficulty)
	// moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
	// returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
	std::pair<int, std::string> move(int &, int &, int &, int &) override;
public:
	Two(int side, int level); // constructor
};

#endif