#include <string>
#include <vector>
#include <utility>
#include "bishop.h"
#include "board.h"
#include "piece.h"
using namespace std;

Bishop::Bishop(bool isWhite) : Piece{isWhite} {
	if (isWhite) {
		representation = "B";
	}
	else {
		representation = "b";
	}
}


// NEW! update fields moves, attacks, checkRoute
void Bishop::updateMovePossibilities() {
	// check if the piece cannot move because of the opposite piece threatening
	Piece * threat = forced;
	if (threat) {
		vector<int[2]> newMoves{};
		vector<int[2]> newAttacks{};
		for (int i = 0; i < threat->getCheckRoute().size(); i += 1) {
			int * possibleMove {threat->getCheckRoute().at(i)};
			int c = canMove(possibleMove[0], possibleMove[1]);
			if (c == 1) newMoves.emplace_back(possibleMove);
			else if (c == 2) newAttacks.emplace_back(possibleMove);
		}	// the piece can move only if the move still block the opposite piece from checking.
		moves = newMoves;
		attacks = newAttacks;
		froced = nullptr;
	}
	else {
		moves = vector<int[2]>{};
		attacks = vector<int[2]>{};
	} 	// clean

	// scan the 4 directions {tr, tl, br, bl}, false if goes out of bound or enounters at lease 2 pieces (opposite) or enounters at lease 1 piece (mate), record each path
	int dir[4] = {2,2,2,2};	
	vector<int[2]> paths[4];
	Piece *firstEncounter[4] = {nullptr, nullptr, nullptr, nullptr}; // record the first enemy piece that block each path
	for (int i = 1; dir[0] != 0 || dir[1] != 0 || dir[2] != 0 || dir[3] != 0; i += 1){
		int pos[4][2] = {{x+i, y+i}, {x-i, y+i},{x+i, y-i}, {x-i, y-i}};
		for (int j = 0; j < 4; j += 1){	// loop on 4 directions
			// check if out of board
			if (pos[j][0] > 8 || pos[j][1] > 8 || pos[j][0] < 0 || pos[j][1] < 0) dir[j] = 0;
			if (dir[j] > 0) {
				Piece * target = gameBoard->getP(pos[j][0], pos[j][1]); // piece on the next position
				if (dir[j] == 2){
					if(target) {	// if there is a piece on the position
						if (target->isKing() && target->side != side) {
							// if the piece is the king of the enemy
							dir[j] = 0;
							attack.emplace_back(pos[j]);
							checkRoute = path[j] ;
							//notify the other player the king is checked (incompleted)


						}
						else if (target->side != side){
							// the piece is not king but belongs to enemy
							if (!threat) attacks.emplace_back(pos[j]);
							dir[j] -= 1;
							paths[j] .emplace_back(pos[j]);
							firstEncounter[j] = target;
						}
						else // blocked by mate, path stops
							dir[j] = 0;
					}
					else {	//  no piece on that position
							if (!threat) moves.emplace_back(pos[j]);
							paths[j].emplace_back(pos[j]);
					} 	// no block
				}
				else if (dir[j] == 1) {	// has past a enemy piece
					if (target) {
						// the piece will check the king if there is no block 
						if (target->getSide() != side && target->isKing()) {
							checkRoute = paths[j] ;
							firstEncounter[j]->forcedBy(this);
						}
						dir[j] == 0;	
					}
					else {
						if (!threat) moves.emplace_back(pos[j]);
						paths[j] .emplace_back(pos[j]);
					}
				}
			}
		}
	}
}

bool Bishop::kingInCheck(bool isWhite) {
	for (int i = 0; i < upperLeftDiag.size(); ++i) {

		// for bishop, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 
		// If it's the opposite color's king, it's in check


		if (upperLeftDiag[i]) {
			if (side == 0) { // capital letter (white)
				if (upperLeftDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
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
			if (side == 0) { // capital letter (white)
				if (upperRightDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
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
			if (side == 0) { // capital letter (white)
				if (lowerLeftDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
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
			if (side == 1) { // capital letter (white)
				if (lowerRightDiag[i]->getRep() == "k") { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else { // lower case letter (black)
				if (lowerRightDiag[i]->getRep() == "K") { // if white king
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

// attempts to move the bishop
// if successful, will update the position
int Bishop::canMove(int col, int row) {
	for (auto pos : moves) {
		if (pos[0] == col && pos[1] == row) return 1;
	}
	for (auto pos : attacks){
		if (pos[0] == col && pos[1] == row) return 2;
	}
	return 1;
}







// helper function that determines of the bishop in position (x, y) checks the king
bool Bishop::posInCheck(int x, int y) {

	// get the diagonals
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