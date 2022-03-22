// DO NOT MODIFY THIS FILE
#ifndef TWOBOARD_H_
#define TWOBOARD_H_
#include <vector>
#include <iostream>
#include "piece.h"
#include "board.h"

// owns-a piece (OWNS A RELATIONSHIP)
class twoPlayerBoard : public Board {

	Piece* board[8][8]; // array of piece pointers
	History history;
	Player p1;
	Player p2;

public:
	twoPlayerBoard();
	~twoPlayerBoard();
	void origSetup();
	void print();	
	bool end();
	bool validMove();

};

#endif