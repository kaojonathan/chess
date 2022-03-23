#ifndef BOARD_H_
#define BOARD_H_

class Board {
public:
	virtual ~Board();
	virtual void origSetup() = 0;
	virtual void print() = 0;	
	virtual bool end() = 0;
	virtual bool validMove() = 0;
	bool kingInCheck(bool isWhite) = 0;
	virtual void insertNewPiece(string validpiece, string position) = 0;
	virtual void removePiece(string position)= 0;
	virtual bool verifySetup() = 0;
	void updateMovePossibilities() = 0;

	Piece* getPiece(int x, int y) = 0;
};

#endif