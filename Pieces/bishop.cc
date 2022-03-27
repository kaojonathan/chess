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
	}
	else {
		moves = vector<int[2]>{};
		attacks = vector<int[2]>{};
	} 	// clean

	// scan the 4 directions {tr, tl, br, bl}, false if goes out of bound or enounters at lease 2 pieces (opposite) or enounters at lease 1 piece (mate), record each path
	int dir[4] = {2,2,2,2};	
	vector<int[2]> paths[4];
	for (int i = 1; dir[0] || dir[2] || dir[3] || dir[4]; i += 1){
		// check if out of board
		if (x+i > 8 || y+i > 8) dir[0] = 0;
		if (x-i < 0 || y+i > 8) dir[2] = 0;
		if (x+i > 8 || y+i > 8) dir[3] = 0;
		if (x-i < 0 || y+i > 8) dir[4] = 0;
		// tr
		if (dir[0] > 0) {
			int pos[2] = {x+i, y+i};
			Piece * target = gameBoard->getP(pos[1], pos[2]);
			if (dir[0] == 2){
				if(target) {
					if (target->isKing() && target->side != side) {
						dir[0] = 0;
						attack.emplace_back(pos);
						checkRoute = path[0] ;
						//notify the other player the king is checked (incompleted)


					}
					else if (target->side != side){
						if (!threat) attacks.emplace_back(pos);
						dir[0] -= 1;
						path[0] .emplace_back(pos);
					}	// encounter opponent's piece (not king)
					else {
						dir[0] = 0;
					}	// blocked by mate
				}
				else {
						if (!threat) moves.emplace_back(pos);
						path[0] .emplace_back(pos);
				} 	// no block
			}
			else if (dir[0] == 1) {
				if (target) {
					if (target->getSide() != side && target->isKing()) {
						checkRoute = path[0] ;
					} // indirect check
					dir[0] == 0;
				}
				else {
					if (!threat) moves.emplace_back(pos);
						path[0] .emplace_back(pos);
				}
			}
		}
		// tl
		if (dir[1] > 0) {
			int pos[2] = {x-i, y+i};
			Piece * target = gameBoard->getP(pos[1], pos[2]);
			if (dir[1] == 2){
				if(target) {
					if (target->isKing() && target->side != side) {
						dir[1] = 0;
						attack.emplace_back(pos);
						checkRoute = path[1] ;
						//notify the other player the king is checked (incompleted)


					}
					else if (target->side != side){
						if (!threat) attacks.emplace_back(pos);
						dir[1] -= 1;
						path[1] .emplace_back(pos);
					}	// encounter opponent's piece (not king)
					else {
						dir[1] = 0;
					}	// blocked by mate
				}
				else {
						if (!threat) moves.emplace_back(pos);
						path[1] .emplace_back(pos);
				} 	// no block
			}
			else if (dir[1] == 1) {
				if (target) {
					if (target->getSide() != side && target->isKing()) {
						checkRoute = path[1] ;
					} // indirect check
					dir[1] == 0;
				}
				else {
					if (!threat) moves.emplace_back(pos);
						path[1] .emplace_back(pos);
				}
			}
		}
		// br
		if (dir[2] > 0) {
			int pos[2] = {x+i, y-i};
			Piece * target = gameBoard->getP(pos[1], pos[2]);
			if (dir[2] == 2){
				if(target) {
					if (target->isKing() && target->side != side) {
						dir[2] = 0;
						attack.emplace_back(pos);
						checkRoute = path[2] ;
						//notify the other player the king is checked (incompleted)


					}
					else if (target->side != side){
						if (!threat) attacks.emplace_back(pos);
						dir[2] -= 1;
						path[2] .emplace_back(pos);
					}	// encounter opponent's piece (not king)
					else {
						dir[2] = 0;
					}	// blocked by mate
				}
				else {
						if (!threat) moves.emplace_back(pos);
						path[2] .emplace_back(pos);
				} 	// no block
			}
			else if (dir[2] == 1) {
				if (target) {
					if (target->getSide() != side && target->isKing()) {
						checkRoute = path[2] ;
					} // indirect check
					dir[2] == 0;
				}
				else {
					if (!threat) moves.emplace_back(pos);
						path[2] .emplace_back(pos);
				}
			}
		}
		// bl
		if (dir[3] > 0) {
			int pos[2] = {x+i, y+i};
			Piece * target = gameBoard->getP(pos[1], pos[2]);
			if (dir[3] == 2){
				if(target) {
					if (target->isKing() && target->side != side) {
						dir[3] = 0;
						attack.emplace_back(pos);
						checkRoute = path[3] ;
						//notify the other player the king is checked (incompleted)


					}
					else if (target->side != side){
						if (!threat) attacks.emplace_back(pos);
						dir[3] -= 1;
						path[3] .emplace_back(pos);
					}	// encounter opponent's piece (not king)
					else {
						dir[3] = 0;
					}	// blocked by mate
				}
				else {
						if (!threat) moves.emplace_back(pos);
						path[3] .emplace_back(pos);
				} 	// no block
			}
			else if (dir[3] == 1) {
				if (target) {
					if (target->getSide() != side && target->isKing()) {
						checkRoute = path[0] ;
					} // indirect check
					dir[3] == 0;
				}
				else {
					if (!threat) moves.emplace_back(pos);
						path[3] .emplace_back(pos);
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
	if (!gameBoard->checkPos(row, col)) return 0;
	// if the position is not in the board
	if (x == col && y == row) return 0;
	// if move to the same position
	if (col - x != row - y && x - col != row - y) 
		return 0; // if the position is in neither of the 4 directions

	vector<Piece*> way; 	// direction
	int xShift = col- x;
	int yShift = row - y;
	if (xShift < 0)
		way = (yShift < 0) ? lowerLeftDiag : upperLeftDiag;
	else
		way = (yShift < 0) ? lowerRightDiag : upperRightDiag; 
	
	int shiftUnit = (xShift > 0) ? xShift : -xShift;

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