#include <iostream>
#include <string>
#include <vector>
#include "knight.h"
using namespace std;

Knight::Knight(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		representation = "N"
	}
	else {

		representation = "n"
	}
}



void Knight::updateMovePossibilities() override {
	// knight's availible moves

	if ((x - 1 >= 0) && (y + 2 <= 7) {
		leftonedowntwo.emplace_back(gameBoard->getPiece(x - 1, y + 2));
	}

	if ((x - 1 >= 0) && (y - 2 >= 0) {
		leftoneuptwo.emplace_back(gameBoard->getPiece(x - 1, y - 2));
	}


	if ((x + 1 <= 7) && (y + 2 <= 7) {
		rightonedowntwo.emplace_back(gameBoard->getPiece(x + 1, y + 2));
	}

	if ((x + 1 <= 7) && (y - 2 >= 0) {
		rightoneuptwo.emplace_back(gameBoard->getPiece(x + 1, y - 2));
	}




	if ((x + 2 <= 7) && (y + 1 <= 7) {
		downonerighttwo.emplace_back(gameBoard->getPiece(x - 1, y + 2));
	}

	if ((x - 2 >= 0) && (y + 1 <= 7) {
		downonelefttwo.emplace_back(gameBoard->getPiece(x - 1, y - 2));
	}


	if ((x + 2 <= 7) && (y - 1 >= 0) {
		uponerighttwo.emplace_back(gameBoard->getPiece(x + 1, y + 2));
	}

	if ((x - 2 >= 0) && (y - 1 >= 0) {
		uponelefttwo.emplace_back(gameBoard->getPiece(x + 1, y - 2));
	}

}

bool Knight::kingInCheck(bool isWhite) override {
	for (int i = 0; i < leftoneuptwo.size(); ++i) {

		// for knight, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 
		// If it's the opposite color's king, it's in check

		if (leftoneuptwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (leftoneuptwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (leftoneuptwo[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	// same thing for other 7 moves

	for (int i = 0; i < leftonedowntwo.size(); ++i) {

		if (leftonedowntwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (leftonedowntwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (leftonedowntwo[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	for (int i = 0; i < rightoneuptwo.size(); ++i) {

		if (rightoneuptwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (rightoneuptwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (rightoneuptwo[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}


	for (int i = 0; i < rightonedowntwo.size(); ++i) {

		if (rightonedowntwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (rightonedowntwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (rightonedowntwo[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}


	for (int i = 0; i < uponerighttwo.size(); ++i) {

		if (uponerighttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (uponerighttwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (uponerighttwo[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	for (int i = 0; i < downonerighttwo.size(); ++i) {

		if (downonerighttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (downonerighttwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (downonerighttwo[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}


	for (int i = 0; i < uponelefttwo.size(); ++i) {

		if (uponelefttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (uponelefttwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (uponelefttwo[i]->getRep() == "K") { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	for (int i = 0; i < downonelefttwo.size(); ++i) {

		if (downonelefttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (downonelefttwo[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (downonelefttwo[i]->getRep() == "K") { // if white king
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