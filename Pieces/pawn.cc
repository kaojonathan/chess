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



bool Pawn::kingInCheck(bool isWhite) override {

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






























// helper function that determines of the pawn in position (x, y) checks the king
bool Pawn::posInCheck(int x, int y) override {

	if (getSide() == 0) { // white case



		if ((x + 1 <= 7) && (y - 1 >= 0)) {
			if (gameBoard[y - 1][x + 1]) {
				if (gameBoard[y - 1][x + 1]->getRep() == "k") { // can check the king (white takes black)

					return true;
				}

			}
		}

		if ((x - 1 >= 0) && (y - 1 >= 0)) {
			if (gameBoard[y - 1][x - 1]) {
				if (gameBoard[y - 1][x - 1]->getRep() == "k") { // can check the king (white takes black)

					return true;
				}

			}
		}


		// since no king has been checked, return false

		return false;

	}
	else { // black case



		if ((x + 1 <= 7) && (y + 1 <= 7)) {
			if (gameBoard[y + 1][x + 1]) {
				if (gameBoard[y + 1][x + 1]->getRep() == "K") { // can check the king (black takes white)

					return true;
				}

			}
		}

		if ((x - 1 >= 0) && (y + 1 <= 7)) {
			if (gameBoard[y + 1][x - 1]) {
				if (gameBoard[y + 1][x - 1]->getRep() == "K") { // can check the king (black takes white)

					return true;
				}

			}
		}

		// since no king has been checked, return false

		return false;

	}



}



pair<int, int> Pawn::getCheckCoords() {

	if (getSide() == 0) { // white case

		if (forward.size() == 1) {
			if (forward[0]) { // not blank cell

				// don't do anything, piece is blocked and can't capture


			}
			else { // open square

				if (posInCheck(x, y - 1)) { // if the pawn in position (x, y - 1) checks the king

					pair<int, int> coords = { x , y - 1 };
					return coords;
				}


			}


		}

		if ((x + 1 <= 7) && (y - 1 >= 0)) {
			if (gameBoard->getPiece(x + 1, y - 1)) { // if pawn right diagonal has an opposite color piece

				if gameBoard->getPiece(x + 1, y - 1)->getSide() == 1) {

				if (posInCheck(x + 1, y - 1)) { // if the pawn in position (x + 1, y - 1) checks the king

					pair<int, int> coords = { x + 1, y - 1 };
					return coords;
				}

				}

			}
		}

		if ((x - 1 >= 0) && (y - 1 >= 0)) {
			if (gameBoard->getPiece(x - 1, y - 1)) { // if pawn left diagonal has an opposite color piece

				if gameBoard->getPiece(x - 1, y - 1)->getSide() == 1) {

				if (posInCheck(x - 1, y - 1)) { // if the pawn in position (x - 1, y - 1) checks the king

					pair<int, int> coords = { x - 1, y - 1 };
					return coords;
				}

				}



			}


		}

	}
	else {

		if (forward.size() == 1) {
			if (forward[0]) { // not blank cell

				// don't do anything, piece is blocked and can't capture


			}
			else { // open square

				if (posInCheck(x, y + 1)) { // if the bishop in position (x, y + 1) checks the king

					pair<int, int> coords = { x , y + 1 };
					return coords;
				}


			}


		}


		if ((x + 1 <= 7) && (y + 1 <= 7)) {
			if (gameBoard->getPiece(x + 1, y + 1)) { // if pawn right diagonal has an opposite color piece

				if gameBoard->getPiece(x + 1, y + 1)->getSide() == 0) {

				if (posInCheck(x + 1, y + 1)) { // if the pawn in position (x + 1, y + 1) checks the king

					pair<int, int> coords = { x + 1, y + 1 };
					return coords;
				}

				}

			}
		}

		if ((x - 1 >= 0) && (y + 1 <= 7)) {
			if (gameBoard->getPiece(x - 1, y + 1)) { // if pawn left diagonal has an opposite color piece

				if gameBoard->getPiece(x - 1, y + 1)->getSide() == 0) {

				if (posInCheck(x - 1, y + 1)) { // if the pawn in position (x - 1, y + 1) checks the king

					pair<int, int> coords = { x - 1, y + 1 };
					return coords;
				}

				}



			}


		}




	}

	// if there are no possible move positions that check the king

	pair<int, int> coords = { -1, -1 };
	return coords;

}