#include <string>
#include <vector>
#include <utility>
#include "queen.h"
#include "board.h"
#include "piece.h"
using namespace std;

Queen::Queen(bool isWhite) : Piece{ isWhite } {
	value = 9;
	if (isWhite) {
		representation = "Q";
	}
	else {
		representation = "q";
	}
}


void Queen::updateMovePossibilities()  {
	updateStatus(3);
}

// helper function that determines of the queen in position (col, row) checks the king
bool Queen::posInCheck(int col, int row) {
	return enemyKing(mostVal(dScan(col, row, 3)));
}

/*
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
*/