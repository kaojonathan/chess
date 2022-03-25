#include <iostream>
#include <string>
#include <vector>
#include "bishop.h"
#include "board.h"
using namespace std;

Bishop::Bishop(bool isWhite) : Piece{isWhite} {}

// returns the representation of Bishop based on its side
string Bishop::representation() {
	return (side == 0) ? "B" : "b"; 
}

void Bishop::updateMovePossibilities() {
	// get the diagonals
	for (int i = 1; i < 8; ++i) { // lower right
		if ((x + i > 7) || (y + i > 7)) {
			break;
		}
		else {
			lowerRightDiag.emplace_back(gameBoard->getPiece(x + i, y + i)); // need a public getPiece() method
		}
	}

	for (int i = 1; i < 8; ++i) {
		if ((x + i > 7) || (y - i < 0)) { // upper right
			break;
		}
		else {
			upperRightDiag.emplace_back(gameBoard->getPiece(x + i, y - i));
		}
	}

	for (int i = 1; i < 8; ++i) {
		if ((x - i < 0) || (y + i > 7)) { // lower left
			break;
		}
		else {
			lowerLeftDiag.emplace_back(gameBoard->getPiece(x - i, y + i));
		}
	}

	for (int i = 1; i < 8; ++i) {
		if ((x - i < 0) || (y - i < 0)) { // upper left
			break;
		}
		else {
			upperLeftDiag.emplace_back(gameBoard->getPiece(x - i, y - i));
		}
	}
}

bool Bishop::kingInCheck(bool isWhite) {
	for (int i = 0; i < upperLeftDiag.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 
		// If it's the opposite color's king, it's in check


		if (upperLeftDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (upperLeftDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
				if (upperLeftDiag[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}
	}

	// same thing for other three diagonals

	for (int i = 0; i < upperRightDiag.size(); ++i) {

		if (upperRightDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (upperRightDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
				if (upperRightDiag[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}


	}

	for (int i = 0; i < lowerLeftDiag.size(); ++i) {

		if (lowerLeftDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (lowerLeftDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
				if (lowerLeftDiag[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}


	}


	for (int i = 0; i < lowerRightDiag.size(); ++i) {


		if (lowerRightDiag[i]) {
			if (side == 1) { // capital letter (white)
				if (lowerRightDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
				if (lowerRightDiag[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}


	}

	// since no king has been checked, return false

	return false;

}

int Bishop::canMove(int col, int row) {
	if (!gameBoard->checkPos(row, col)) return 0;
	// if the position is not in the board

	if (col - x != row - y && x - col != row - y) 
		return 0; // if the position is in neither of the 4 directions

	vector<Piece*> way; 	// direction
	int xShift = col- x;
	int yShift = row - y;
	if (xShift < 0)
		way = (yShift < 0) ? lowerLeftDiag : upperLeftDiag;
	else
		way = (yShift < 0) ? lowerRightDiag : upperRightDiag; 
	
	int shiftUnit = (xShift > 0) ? xShift : -xShift;

	for (int i = 0; i < shiftUnit-1; i += 1) {
		if (way.at(i)) return 0; // blocked
	}

	Piece * target = way.at(shiftUnit);
	if (target) {
		if (target->getSide() == side) return 0;
		else return 2;
	}
	return 1;
}