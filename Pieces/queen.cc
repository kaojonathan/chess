#include <iostream>
#include <string>
#include <vector>
#include "queen.h"
using namespace std;

Queen::Queen(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		representation = "Q"
	}
	else {

		representation = "q"
	}
}


void Queen::updateMovePossibilities() override {
	// get the cross
	for (int i = 1; i < 8; ++i) { // right
		if (x + i > 7) {
			break;
		}
		else {
			right.emplace_back(gameBoard->getPiece(x + i, y));
		}
	}

	for (int i = 1; i < 8; ++i) {
		if (x - i < 0) { // left
			break;
		}
		else {
			left.emplace_back(gameBoard->getPiece(x - i, y));
		}


	}
	for (int i = 1; i < 8; ++i) { // down
		if (y + i > 7) {
			break;
		}
		else {
			down.emplace_back(gameBoard->getPiece(x, y + i));
		}
	}

	for (int i = 1; i < 8; ++i) {
		if (y - i < 0) { // up
			break;
		}
		else {
			up.emplace_back(gameBoard->getPiece(x, y - i));
		}
	}



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

bool Queen::kingInCheck(bool isWhite) override {

	for (int i = 0; i < upperLeftDiag.size(); ++i) {

		// for queen, check diagonals and cross, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 
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


	// now check the cross


	for (int i = 0; i < up.size(); ++i) {


		if (up[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (up[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (up[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}


	}

	// same thing for other three ways

	for (int i = 0; i < down.size(); ++i) {


		if (down[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (down[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (down[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}


	}

	for (int i = 0; i < left.size(); ++i) {


		if (left[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (left[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (left[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}


	}


	for (int i = 0; i < right.size(); ++i) {


		if (right[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (right[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (right[i]->getRep() == "K") { // if white king
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