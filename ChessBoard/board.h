// DO NOT MODIFY THIS FILE
#ifndef BOARD_H_
#define BOARD_H_


// has-a piece
class Board {

	History history;
	Piece piece;
	Player p1;
	Player p2;

public:
	Board();
	~Board();
	void print();
	bool end();
	bool validMove();

};

#endif