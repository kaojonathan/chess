// DO NOT MODIFY THIS FILE
#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <iostream>
#include "piece.h"

// owns-a piece (OWNS A RELATIONSHIP)
class Board {

	Piece* board[8][8]; // array of piece pointers
	History history;
	Player p1;
	Player p2;

public:
	Board();
	~Board();
	void origSetup();
	void print();	
	bool end();
	bool validMove();

};

#endif