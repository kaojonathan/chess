#ifndef BOARD_H_
#define BOARD_H_
#include "piece.h"
#include <string>

class Board {
	virtual ~Board();
	virtual void origSetup() = 0;
	virtual void print() = 0;	
	virtual bool end() = 0;
	virtual bool validMove() = 0;
	virtual bool kingInCheck(bool isWhite) = 0;
	virtual void insertNewPiece(std::string validpiece, std::string position) = 0;
	virtual void removePiece(std::string position)= 0;
	virtual bool verifySetup() = 0;
	virtual void updateMovePossibilities() = 0; // updates each Piece's possible moves (uses polymorphism)
	virtual Piece* getPiece(int x, int y) = 0;
		
};

#endif