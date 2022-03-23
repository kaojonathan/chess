#include <iostream>
#include <string>
#include <vector>
#include "bishop.h"
using namespace std;

Bishop::Bishop(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		representation = "B"
	}
	else {

		representation = "b"
	}
}



void Bishop::updateMovePossibilities() override {
	// get the diagonals
	for (int i = 1; i < 8; ++i) { // lower right
		if ((x + i > 7) || (y + i > 7)) {
			break;
		}
		else {
			lowerRightDiag.emplace_back(gameBoard->getPiece(x + i, y + i));
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

bool Bishop::kingInCheck(bool isWhite) override {
	for (int i = 0; i < upperLeftDiag.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 
		// If it's the opposite color's king, it's in check

		if (upperLeftDiag[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (upperLeftDiag[i]->getRep() == "k") { // if black king

					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
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
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (upperRightDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
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
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (lowerLeftDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
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
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (lowerRightDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
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