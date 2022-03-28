#include <string>
#include <vector>
#include <utility>
#include "rook.h"
#include "board.h"
using namespace std;

Rook::Rook(bool isWhite) : Piece{isWhite} {
	value = 6;
	if (isWhite) {
		representation = "R";
	}
	else {

		representation = "r";
	}
}

void Rook::updateMovePossibilities() {
	updateStatus(2);
}

// helper function that determines of the bishop in position (x, y) checks the king
bool Rook::posInCheck(int col, int row) {
	enemyKing(mostVal(dScan(col, row, 2)));
}


/*
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
*/