#ifndef TWOBOARD_H_
#define TWOBOARD_H_
#include "board.h"
class Piece;


class twoPlayerBoard : public Board {
	Piece* board[8][8]; // array of piece pointers
	void insertNewPiece(std::string validpiece, std::string position) override;
	void removePiece(std::string position) override;
	Piece* getP(int x, int y) override; // getter
	void movePiece(int x, int y, int newx, int newy) override; // setter
	// setter
	void set(int x, int y, Piece * p) override;

	bool verifySetup() override;
	void origSetup() override;

	void capturePiece(int newx, int newy) override;

	void castle(int col, int row) override;
	void undoCastle(int col, int row) override;


public:
	twoPlayerBoard();
	bool validPos(int, int) override; // basic method, returns false if the position is out of the board
};

#endif