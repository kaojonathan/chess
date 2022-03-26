#include <string>
#include <vector>
#include "rook.h"
#include "board.h"
using namespace std;

Rook::Rook(bool isWhite) : Piece{isWhite} {
	if (isWhite) {
		representation = "R";
	}
	else {

		representation = "r";
	}
}



void Rook::updateMovePossibilities() {
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
}


bool Rook::kingInCheck(bool isWhite) {
	for (int i = 0; i < up.size(); ++i) {

		// for rook, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 
		// If it's the opposite color's king, it's in check

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



int Rook::canMove(int col, int row) {
	if (!gameBoard->checkPos(row, col)) return 0;
	// if the position is not in the board
	if (x == col && y == row) return 0;
	// if move to the same position
	if ( x != col && y != row) 
		return 0; // if the position is in neither of the 4 directions

	vector<Piece*> way; 	// direction
	int xShift = col - x;
	int yShift = row - y;
	int shiftUnit = 0;
	if (xShift == 0) {
		way = (yShift < 0) ? down : up;
		shiftUnit = (yShift < 0) ? -yShift : yShift;
	}
	else if (yShift == 0) {
		way = (xShift < 0) ? left : right;
		shiftUnit = (xShift < 0) ? -xShift : xShift;
	}
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





































// helper function that determines of the bishop in position (x, y) checks the king
bool Rook::posInCheck(int x, int y) {

	// get the cross
	for (int i = 1; i < 8; ++i) { // right
		if (x + i > 7) {
			break;
		}
		else if (gameBoard->getPiece(x + i, y)) {

			if ((gameBoard->getPiece(x + i, y)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;


			}
			else if ((gameBoard->getPiece(x + i, y)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;

			}
			break;
		}

		// keep iterating on open square
	}

	for (int i = 1; i < 8; ++i) { // left
		if (x - 1 < 0) {
			break;
		}
		else if (gameBoard->getPiece(x - i, y)) {

			if ((gameBoard->getPiece(x - i, y)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;
			}
			else if ((gameBoard->getPiece(x - i, y)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;

			}
			break;
		}
		// keep iterating on open square
	}

	for (int i = 1; i < 8; ++i) { // down
		if (y + i > 7) {
			break;
		}
		else if (gameBoard->getPiece(x, y + i)) {

			if ((gameBoard->getPiece(x, y + i)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;


			}
			else if ((gameBoard->getPiece(x, y + i)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;

			}
			break;
		}
		// keep iterating on open square
	}


	for (int i = 1; i < 8; ++i) { // up
		if (y - i < 0) {
			break;
		}
		else if (gameBoard->getPiece(x, y - i)) {

			if ((gameBoard->getPiece(x, y - i)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;


			}
			else if ((gameBoard->getPiece(x, y - i)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;
			}
			break;
		}
		// keep iterating on open square
	}

	// since no king has been checked, return false

	return false;

}



pair<int, int> Rook::getCheckCoords() {

	for (int i = 0; i < up.size(); ++i) {

		// for rook, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (up[i]) {
			if (side == 0) { // capital letter (white)
				if (up[i]->getSide() == 1) { // if black piece


					if (posInCheck(x, y - i)) { // if the bishop in position (x, y - i) checks the king

						pair<int, int> coords = { x, y - i };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (up[i]->getSide() == 0) { // if white piece


					if (posInCheck(x, y - i)) { // if the bishop in position (x, y - i) checks the king

						pair<int, int> coords = { x, y - i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x, y - i)) { // if the bishop in position (x, y - i) checks the king

				pair<int, int> coords = { x, y - i };
				return coords;
			}


		}
	}



	for (int i = 0; i < right.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (right[i]) {
			if (side == 0) { // capital letter (white)
				if (right[i]->getSide() == 1) { // if black piece


					if (posInCheck(x + i, y)) { // if the bishop in position (x + i, y) checks the king

						pair<int, int> coords = { x + i, y };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (right[i]->getSide() == 0) { // if white piece


					if (posInCheck(x + i, y)) { // if the bishop in position (x + i, y) checks the king

						pair<int, int> coords = { x + i, y };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x + i, y)) { // if the bishop in position (x + i, y) checks the king

				pair<int, int> coords = { x + i, y };
				return coords;
			}


		}
	}



	for (int i = 0; i < down.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (down[i]) {
			if (side == 0) { // capital letter (white)
				if (down[i]->getSide() == 1) { // if black piece


					if (posInCheck(x, y + i)) { // if the bishop in position (x, y + i) checks the king

						pair<int, int> coords = { x, y + i };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (down[i]->getSide() == 0) { // if white piece


					if (posInCheck(x, y + i)) { // if the bishop in position (x, y + i) checks the king

						pair<int, int> coords = { x, y + i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x, y + i)) { // if the bishop in position (x, y + i) checks the king

				pair<int, int> coords = { x, y + i };
				return coords;
			}


		}
	}




	for (int i = 0; i < left.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (left[i]) {
			if (side == 0) { // capital letter (white)
				if (left[i]->getSide() == 1) { // if black piece


					if (posInCheck(x - i, y)) { // if the bishop in position (x - i, y) checks the king

						pair<int, int> coords = { x - i, y };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (left[i]->getSide() == 0) { // if white piece


					if (posInCheck(x - i, y)) { // if the bishop in position (x - i, y) checks the king

						pair<int, int> coords = { x - i, y };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x - i, y)) { // if the bishop in position (x - i, y) checks the king

				pair<int, int> coords = { x - i, y };
				return coords;
			}


		}
	}

	// if there are no possible move positions that check the king

	pair<int, int> coords = { -1, -1 };
	return coords;

}