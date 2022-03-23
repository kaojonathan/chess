#include <iostream>
#include <string>
#include <vector>
#include "pawn.h"
using namespace std;

Pawn::Pawn(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		representation = "P"
	}
	else {

		representation = "p"
	}
}


void Pawn::updateMovePossibilities() override {

	if (representation == "P") { // white

		if (numMoves < 1) {

			for (int i = 1; i < 3; ++i) {
				if (y - i < 0) { // up
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y - i));
				}
			}

		}
		else {

			for (int i = 1; i < 2; ++i) {
				if (y - i < 0) { // up
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y - i));
				}
			}



		}


	}
	else { // black

		if (numMoves < 1) {

			for (int i = 1; i < 3; ++i) { // down
				if (y + i > 7) {
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y + i));
				}
			}


		}
		else {
			for (int i = 1; i < 2; ++i) { // down
				if (y + i > 7) {
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y + i));
				}
			}


		}


	}
}



bool Pawn::kingInCheck() override {

	// just check forward one square diagonals i think

	if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)

		if ((x + 1 <= 7) && (y - 1 >= 0)) {
			if (gameBoard->getPiece(x + 1, y - 1)->getRep() == "k") {// if black king
				if (isWhite) {
					return true;
				}
			}


		}
		else if ((x - 1 >= 0) && (y - 1 >= 0)) {

			if (gameBoard->getPiece(x - 1, y - 1)->getRep() == "k") {// if black king
				if (isWhite) {
					return true;
				}
			}

		}


	}
	else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)

		if ((x + 1 <= 7) && (y + 1 <= 7)) {
			if (gameBoard->getPiece(x + 1, y - 1)->getRep() == "K") {// if white king
				if (!isWhite) {
					return true;
				}
			}


		}
		else if ((x - 1 >= 0) && (y + 1 <= 7)) {

			if (gameBoard->getPiece(x - 1, y - 1)->getRep() == "K") {// if white king
				if (!isWhite) {
					return true;
				}
			}

		}


	}
	// since no king has been checked, return false
	return false;

}