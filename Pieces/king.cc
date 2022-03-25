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


void King::updateMovePossibilities() override {
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

