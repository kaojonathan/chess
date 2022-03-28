#ifndef TWOBOARD_H_
#define TWOBOARD_H_
#include "board.h"
class Piece;

// owns-a piece (OWNS A RELATIONSHIP)
class twoPlayerBoard : public Board {
	Piece* board[8][8]; // array of piece pointers
	
	void origSetup() override;
	void print() override;	
	bool end() override; // implementation required?
	bool kingInCheck(bool isWhite) override;
	void insertNewPiece(std::string validpiece, std::string position) override;
	void removePiece(std::string position) override;
	bool verifySetup() override;
	Piece* getP(int x, int y) override; // getter
	void movePiece(int x, int y, int newx, int newy); // setter
	void updateBoardMoves() override; // every time the board changes, call this


public:
	twoPlayerBoard();
	~twoPlayerBoard(); // needs implementation
	bool validPos(int, int) override; // basic method, returns false if the position is out of the board

};

#endif