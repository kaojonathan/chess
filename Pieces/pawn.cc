#include <string>
#include <vector>
#include <utility>
#include "pawn.h"
#include "../Board/board.h"
#include "../Players/player.h"
using namespace std;


Pawn::Pawn(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 1; // change after the first move?
	representation = (side == 0) ? "P" : "p";
}

int Pawn::frDir(){ return (side == 0) ? -1 : 1; }

std::vector<Piece *> Pawn::attackable(std::pair<int, int> at) {
	vector <Piece *> res {};
	int dir = frDir();
	if (at.second + dir  >= 8 || at.second + dir < 0) return res;
	if (at.first-1 < 8 && at.first-1 >= 0) {
		Piece *target = gameBoard->getPiece(at.first-1, at.second);
		if (target && (target->getSide() != side))  res.emplace_back(target);
	}
	if (at.first+1 < 8 && at.first+1 >= 0) {
		Piece *target = gameBoard->getPiece(at.first+1, at.second);
		if (target && (target->getSide() != side))  res.emplace_back(target);
	}
	return res;
}

void Pawn::nUpdate() {
	updateStatus = 1;
	int dir = (side == 0) ? -1 : 1;	// forward dircection
	int fr = y + dir;
	if (fr < 8 && fr >= 0) {
		if (!gameBoard->getPiece(x, fr)) moves.emplace_back(pair<int, int>{x,fr});
		for (int sd : vector<int> {x-1, x + 1}){
			if (sd < 8 && sd >= 0) {
				Piece * target = gameBoard->getPiece(sd, fr);
				if (target) {
					if (target->getSide() != side) {
						if (enemyKing(target)) {
							checkRoute.emplace_back(pair<int, int>{sd,fr});
							opponent->kingCheckedBy(this);
						}
						targets.emplace_back(pair<int, int>{sd,fr});
					}
				}
			}
		}
	}
	fr += dir;
	if (numMoves == 0 && fr < 8 && fr >= 0 && !gameBoard->getPiece(x, fr))
		moves.emplace_back(pair<int, int>{x,fr});
}



/* DEBUG
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

				if (gameBoard->getPiece(x + 1, y - 1)->getSide() == 1) {

				if (posInCheck(x + 1, y - 1)) { // if the pawn in position (x + 1, y - 1) checks the king

					pair<int, int> coords = { x + 1, y - 1 };
					return coords;
				}

				}

			}
		}

		if ((x - 1 >= 0) && (y - 1 >= 0)) {
			if (gameBoard->getPiece(x - 1, y - 1)) { // if pawn left diagonal has an opposite color piece

				if (gameBoard->getPiece(x - 1, y - 1)->getSide() == 1) {

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

				if (gameBoard->getPiece(x + 1, y + 1)->getSide() == 0) {

				if (posInCheck(x + 1, y + 1)) { // if the pawn in position (x + 1, y + 1) checks the king

					pair<int, int> coords = { x + 1, y + 1 };
					return coords;
				}

				}

			}
		}

		if ((x - 1 >= 0) && (y + 1 <= 7)) {
			if (gameBoard->getPiece(x - 1, y + 1)) { // if pawn left diagonal has an opposite color piece

				if (gameBoard->getPiece(x - 1, y + 1)->getSide() == 0) {

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
*/