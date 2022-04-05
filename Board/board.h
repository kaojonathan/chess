#ifndef BOARD_H_
#define BOARD_H_
#include "../Pieces/piece.h"
#include <string>
#include <memory>

class Board
{ // the chess game board class. essentially the main controller of the entire game. abstract
protected:
	virtual void insertNewPiece(std::string validpiece, std::string position) = 0; // inserts a new valid piece at position
	virtual void removePiece(std::string position) = 0; // removes a piece at position
	virtual std::shared_ptr<Piece> shareP(int, int) = 0; // returns a shared pointer of the piece at pos (x, y)
	virtual Piece *getP(int, int) = 0; // returns a raw pointer of the piece at pos (x, y)
	virtual void movePiece(int x, int y, int newx, int newy) = 0; // moves a piece at position (x, y) to (newx, newy)
	virtual bool validPos(int, int) = 0; // checks if (x, y) is a valid position on the board
	virtual bool verifySetup() = 0; // verifies if the setup of the chess pieces is valid according to the assignment guidelines
	virtual void origSetup() = 0; // sets up the board with pieces like an original chess game
	virtual void capturePiece(int newx, int newy) = 0; // captures the piece at pos (newx, newy)
	virtual void castle(int col, int row) = 0; // performs castle at pos (col, row)
public:
	Board(); // constructor
	virtual ~Board() = 0; // destructor
	bool checkPos(int, int); // checks if the position at (x, y) is valid
	std::shared_ptr<Piece> sharePiece(int x, int y)
	{ // returns a shared pointer of the piece at pos (x, y)
		return shareP(x, y);
	}
	Piece *getPiece(int x, int y)
	{ // returns a raw pointer of the piece at pos (x, y)
		return getP(x, y);
	}
	void moveP(int x, int y, int newx, int newy)
	{ // moves a piece at position (x, y) to (newx, newy)
		movePiece(x, y, newx, newy);
	}
	void removeP(std::string position)
	{ // removes a piece at position
		removePiece(position);
	}
	void insertP(std::string p, std::string pos)
	{ // inserts a new valid piece at position
		insertNewPiece(p, pos);
	}
	bool verify()
	{ // verifies if the setup of the chess pieces is valid according to the assignment guidelines
		return verifySetup();
	}
	void oSetup()
	{ // sets up the board with pieces like an original chess game
		origSetup();
	}
	void captureP(int newx, int newy)
	{ // captures the piece at pos (newx, newy)
		capturePiece(newx, newy);
	}
	void doCastle(int col, int row)
	{ // performs castle at pos (col, row)
		castle(col, row);
	}
};

#endif