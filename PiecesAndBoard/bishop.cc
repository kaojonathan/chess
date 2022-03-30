#include <string>
#include <vector>
#include <utility>
#include "bishop.h"
#include "board.h"
#include "piece.h"
using namespace std;

Bishop::Bishop(bool isWhite) : Piece{isWhite} {
	value = 3;
	if (isWhite) {
		representation = "B";
	}
	else {
		representation = "b";
	}
}


// normal status update, assuming it is not forced
void Bishop::nUpdate() {
	updateStatus = 1;
	dirScan(1);
}

// check if the emeny king is checked
// edit now it is not pure virtual

// attempts to move the bishop
// if successful, will update the position 
// [Edit: updating the position should be implemented by a board/player/main method, so that the board can check if the move is invalid and ask player to enter the correct comment. This method can only return the validity of the move, cannot move the piece. edit2: now it is not pure virtual]

std::vector<Piece *> Bishop::attackable(std::pair<int, int> at) {
	return dScan(at, 1);
}

/*
pair<int, int> Bishop::getCheckCoords() {

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