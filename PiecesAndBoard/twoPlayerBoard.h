#ifndef TWOBOARD_H_
#define TWOBOARD_H_
#include "board.h"
#include <memory>
class Piece;


class twoPlayerBoard : public Board {
	std::shared_ptr<Piece> board[8][8]; // array of piece pointers
	void insertNewPiece(std::string validpiece, std::string position) override;
	void removePiece(std::string position) override;
	std::shared_ptr<Piece> shareP(int x, int y) override; // sharer for players
	Piece* getP(int x, int y) override; // used for general getter
	void movePiece(int x, int y, int newx, int newy) override; // setter
	bool verifySetup() override;
	void origSetup() override;

	void capturePiece(int newx, int newy) override;

	void castle(int col, int row) override;


public:
	twoPlayerBoard();
	bool validPos(int, int) override; // basic method, returns false if the position is out of the board
};

#endif