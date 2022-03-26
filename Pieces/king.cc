#include <string>
#include <vector>
#include "king.h"
#include "board.h"
using namespace std;

King::King(bool isWhite) : Piece{ isWhite } {
	if (isWhite) {
		representation = "K";
	}
	else {

		representation = "k";
	}
}

King::~King() {
}


void King::updateMovePossibilities() {
	if (x + 1 <= 7) {
		right.emplace_back(gameBoard->getPiece(x + 1, y));
	}

	if (x - 1 >= 0) {
		left.emplace_back(gameBoard->getPiece(x - 1, y));

	}

	if (y + 1 <= 7) {
		down.emplace_back(gameBoard->getPiece(x, y + 1));

	}

	if (y - 1 >= 0) {
		up.emplace_back(gameBoard->getPiece(x, y - 1));

	}


		if ((x + 1 <= 7) && (y + 1 <= 7)) {
			downright.emplace_back(gameBoard->getPiece(x + 1, y + 1));
		}

		if ((x + 1 <= 7) && (y - 1 >= 0)) {
			upright.emplace_back(gameBoard->getPiece(x + 1, y - 1));
		}


		if ((x - 1 >= 0) && (y + 1 <= 7)) {
			downleft.emplace_back(gameBoard->getPiece(x - 1, y + 1));
		}

		if ((x - 1 >= 0) && (y - 1 >= 0)) {
			upleft.emplace_back(gameBoard->getPiece(x - 1, y - 1));
		}
}

// king does not have kingInCheck method since that could never happen

int King::canMove(int col, int row){
	if (!gameBoard->checkPos(row, col)) return 0;
	// if the position is not in the board
	
		if (x == col && y == row) return 0;
	// if move to the same position

	if ((col - x >= 1 || col - x <= -1 || row - y >=  1 ||  row - y <= -1) && !cancastle) 
		return 0; // if the position is in neither of the 4 directions
	Piece *target =  gameBoard->getPiece(col, row);
	if (target && target->getSide() == side) return 0;
	return 1;
	// determine if the move make the king in check, and if a castling is valid not implemented yet

}