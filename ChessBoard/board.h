#ifndef BOARD_H_
#define BOARD_H_

class Board {
public:
	virtual ~Board();
	virtual void origSetup() = 0;
	virtual void print() = 0;	
	virtual bool end() = 0;
	virtual bool validMove() = 0;
};

#endif