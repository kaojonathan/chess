#include <string>
#include <vector>
#include <utility>
#include "queen.h"
#include "board.h"
using namespace std;

Queen::Queen(bool isWhite) : Piece{ isWhite } {
	if (isWhite) {
		representation = "Q";
	}
	else {

		representation = "q";
	}
}


void Queen::updateMovePossibilities()  {
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

bool Queen::kingInCheck(bool isWhite)  {

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





int Queen::canMove(int col, int row) {
		if (!gameBoard->checkPos(row, col)) return 0;
	// if the position is not in the board
	if (x == col && y == row) return 0;
	// if move to the same position
	if (col - x != row - y && x - col != row - y && x != col && y != row) 
		return 0; // if the position is in neither of the 8 directions

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
	else if (xShift < 0) {
		way = (yShift < 0) ? lowerLeftDiag : upperLeftDiag;
		shiftUnit = (yShift < 0) ? -yShift : yShift;
	}
	else {
		way = (yShift < 0) ? lowerRightDiag : upperRightDiag;
		shiftUnit = (yShift < 0) ? -yShift : yShift;
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














































// helper function that determines of the queen in position (x, y) checks the king
bool Queen::posInCheck(int x, int y) {

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




	/////// now check the diagonals /////////////////





	for (int i = 1; i < 8; ++i) { // lower right
		if ((x + i > 7) || (y + i > 7)) {
			break;
		}
		else if (gameBoard->getPiece(x + i, y + i)) {

			if ((gameBoard->getPiece(x + i, y + i)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;


			}
			else if ((gameBoard->getPiece(x + i, y + i)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;

			}
			break;
		}

		// keep iterating on open square
	}

	for (int i = 1; i < 8; ++i) { // upper right
		if ((x + i > 7) || (y - i < 0)) {
			break;
		}
		else if (gameBoard->getPiece(x + i, y - i)) {

			if ((gameBoard->getPiece(x + i, y - i)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;


			}
			else if ((gameBoard->getPiece(x + i, y - i)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;

			}
			break;
		}
		// keep iterating on open square
	}

	for (int i = 1; i < 8; ++i) { // lower left
		if ((x - i < 0) || (y + i > 7)) {
			break;
		}
		else if (gameBoard->getPiece(x - i, y + i)) {

			if ((gameBoard->getPiece(x - i, y + i)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;


			}
			else if ((gameBoard->getPiece(x - i, y + i)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;

			}
			break;
		}
		// keep iterating on open square
	}


	for (int i = 1; i < 8; ++i) { // upper left
		if ((x - i < 0) || (y - i < 0)) {
			break;
		}
		else if (gameBoard->getPiece(x - i, y - i)) {

			if ((gameBoard->getPiece(x - i, y - i)->getRep() == "K") && (this->getSide() == 1)) { // can check the king (black takes white)

				return true;


			}
			else if ((gameBoard->getPiece(x - i, y - i)->getRep() == "k") && (this->getSide() == 0)) { // can check the king (white takes black)

				return true;
			}
			break;
		}
		// keep iterating on open square
	}





	// since no king has been checked, return false

	return false;

}



pair<int, int> Queen::getCheckCoords() {

	for (int i = 0; i < up.size(); ++i) {

		// for queen, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (up[i]) {
			if (side == 0) { // capital letter (white)
				if (up[i]->getSide() == 1) { // if black piece


					if (posInCheck(x, y - i)) { // if the queen in position (x, y - i) checks the king

						pair<int, int> coords = { x, y - i };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (up[i]->getSide() == 0) { // if white piece


					if (posInCheck(x, y - i)) { // if the queen in position (x, y - i) checks the king

						pair<int, int> coords = { x, y - i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x, y - i)) { // if the queen in position (x, y - i) checks the king

				pair<int, int> coords = { x, y - i };
				return coords;
			}


		}
	}



	for (int i = 0; i < right.size(); ++i) {

		// for queen, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (right[i]) {
			if (side == 0) { // capital letter (white)
				if (right[i]->getSide() == 1) { // if black piece


					if (posInCheck(x + i, y)) { // if the queen in position (x + i, y) checks the king

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

		// for queen, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


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


					if (posInCheck(x, y + i)) { // if the queen in position (x, y + i) checks the king

						pair<int, int> coords = { x, y + i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x, y + i)) { // if the queen in position (x, y + i) checks the king

				pair<int, int> coords = { x, y + i };
				return coords;
			}


		}
	}




	for (int i = 0; i < left.size(); ++i) {

		// for queen, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (left[i]) {
			if (side == 0) { // capital letter (white)
				if (left[i]->getSide() == 1) { // if black piece


					if (posInCheck(x - i, y)) { // if the queen in position (x - i, y) checks the king

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


	///////////// now check diagonals /////////////////


	for (int i = 0; i < upperLeftDiag.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (upperLeftDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (upperLeftDiag[i]->getSide() == 1) { // if black piece


					if (posInCheck(x - i, y - i)) { // if the bishop in position (x - i, y - i) checks the king

						pair<int, int> coords = { x - i, y - i };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (upperLeftDiag[i]->getSide() == 0) { // if white piece


					if (posInCheck(x - i, y - i)) { // if the bishop in position (x - i, y - i) checks the king

						pair<int, int> coords = { x - i, y - i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x - i, y - i)) { // if the bishop in position (x - i, y - i) checks the king

				pair<int, int> coords = { x - i, y - i };
				return coords;
			}


		}
	}



	for (int i = 0; i < upperRightDiag.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (upperRightDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (upperRightDiag[i]->getSide() == 1) { // if black piece


					if (posInCheck(x + i, y - i)) { // if the bishop in position (x + i, y - i) checks the king

						pair<int, int> coords = { x + i, y - i };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (upperRightDiag[i]->getSide() == 0) { // if white piece


					if (posInCheck(x + i, y - i)) { // if the bishop in position (x + i, y - i) checks the king

						pair<int, int> coords = { x + i, y - i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x + i, y - i)) { // if the bishop in position (x + i, y - i) checks the king

				pair<int, int> coords = { x + i, y - i };
				return coords;
			}


		}
	}



	for (int i = 0; i < lowerLeftDiag.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (lowerLeftDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (lowerLeftDiag[i]->getSide() == 1) { // if black piece


					if (posInCheck(x - i, y + i)) { // if the bishop in position (x - i, y + i) checks the king

						pair<int, int> coords = { x - i, y + i };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (lowerLeftDiag[i]->getSide() == 0) { // if white piece


					if (posInCheck(x - i, y + i)) { // if the bishop in position (x - i, y + i) checks the king

						pair<int, int> coords = { x - i, y + i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x - i, y + i)) { // if the bishop in position (x - i, y + i) checks the king

				pair<int, int> coords = { x - i, y + i };
				return coords;
			}


		}
	}




	for (int i = 0; i < lowerRightDiag.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 


		if (lowerRightDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (lowerRightDiag[i]->getSide() == 1) { // if black piece


					if (posInCheck(x + i, y + i)) { // if the bishop in position (x + i, y + i) checks the king

						pair<int, int> coords = { x + i, y + i };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (lowerRightDiag[i]->getSide() == 0) { // if white piece


					if (posInCheck(x + i, y + i)) { // if the bishop in position (x + i, y + i) checks the king

						pair<int, int> coords = { x + i, y + i };
						return coords;
					}


				}
			}
			break;
		}
		else { // open square

			if (posInCheck(x + i, y + i)) { // if the bishop in position (x + i, y + i) checks the king

				pair<int, int> coords = { x + i, y + i };
				return coords;
			}


		}
	}


	// if there are no possible move positions that check the king

	pair<int, int> coords = { -1, -1 };
	return coords;

}