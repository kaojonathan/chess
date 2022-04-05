#ifndef THREE_H_
#define THREE_H_
#include "computer.h"

class Three : public Computer
{ // three is a type of computer (difficulty)
	// moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
	// returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
	std::pair<int, std::string> move(int &, int &, int &, int &) override;
public:
 	// constructor
	Three(int side, int level);
};

#endif