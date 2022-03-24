// DO NOT MODIFY THIS FILE
#ifndef TWOBOARD_H_
#define TWOBOARD_H_
#include <vector>
#include <iostream>
#include "piece.h"
#include "board.h"

// owns-a piece (OWNS A RELATIONSHIP)
class twoPlayerBoard : public Board {
	Piece* board[8][8]; // array of piece pointers
	History history;
	Player white;
	Player black;

public:
	twoPlayerBoard();
	~twoPlayerBoard();
	void origSetup() override;
	void print() override;	
	bool end() override;
	bool validMove() override;
	bool kingInCheck(bool isWhite) override;
	void insertNewPiece(string validpiece, string position) override;
	void removePiece(string position) override;
	bool verifySetup() override;




	Piece* getPiece(int x, int y); // getter
	void movePiece(int x, int y, int newx, int newy); // setter



	void updateMovePossibilities() override; // every time the board changes, call this

};

#endif