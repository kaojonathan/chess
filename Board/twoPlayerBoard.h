#ifndef TWOBOARD_H_
#define TWOBOARD_H_
#include "board.h"
#include <memory>
class Piece;


class twoPlayerBoard : public Board { // the concrete chess game board class. essentially the main controller of the entire game.
	std::shared_ptr<Piece> board[8][8]; // array of piece pointers (board implementation)
	void insertNewPiece(std::string validpiece, std::string position) override; // inserts a new valid piece at position
	void removePiece(std::string position) override; // removes a piece at position
	std::shared_ptr<Piece> shareP(int x, int y) override; // returns a shared pointer of the piece at pos (x, y)
	Piece* getP(int x, int y) override; // returns a raw pointer of the piece at pos (x, y)
	void movePiece(int x, int y, int newx, int newy) override; // moves a piece at position (x, y) to (newx, newy)
	bool verifySetup() override; // verifies if the setup of the chess pieces is valid according to the assignment guidelines
	void origSetup() override; // sets up the board with pieces like an original chess game
	void capturePiece(int newx, int newy) override; // captures the piece at pos (x, y)
	void castle(int col, int row) override; // performs castle at pos (col, row)
public:
	twoPlayerBoard(); // constructor
	bool validPos(int, int) override; // checks if (x, y) is a valid position on the board
};

#endif