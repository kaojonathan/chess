#include <string>
#include <vector>
#include <utility>
#include "pawn.h"
#include "board.h"
using namespace std;

Pawn::Pawn(bool isWhite) : Piece{ isWhite } {
	value = 1; // change after the first move?
	if (isWhite) {
		representation = "P";
	}
	else {
		representation = "p";
	}
}

 vector<pair<int,int>> Pawn::getPos(int col, int row){
	vector<pair<int,int>> res{};
	int dir = (side == 0) ? 1 : -1;
	if (row + dir < 8 && row + dir >= 0) res.emplace_back(pair{col, row + dir}); 
	if (numMoves == 0 && row + 2*dir < 8 && row + 2*dir >= 0) res.emplace_back(pair{col, row +dir});
	return res;
 }

std::vector<Piece *> Pawn::attackable(std::pair<int, int> at) {
	vector <Piece *> res {};
	int dir = (side == 0) ? 1 : -1;
	if (at.second + dir >= 8 &&  at.second + dir < 0) return res;
	if (at.first-1 >= 0) {
		Piece *target = gameBoard->getPiece(at.first-1, at.second);
		if (target && (target->getSide() != side))  res.emplace_back(target);
	}
	if (at.first+1 < 8) {
		Piece *target = gameBoard->getPiece(at.first+1, at.second);
		if (target && (target->getSide() != side))  res.emplace_back(target);
	}
	return res;
}

void Pawn::updateMovePossibilities() {
	int dir = (side == 0) ? 1 : -1;	// forward dircection
	if (forced) {
		vector<pair<pair<int,int>, vector<Piece *>>> newMoves{};
		vector<pair<int,int>> newAttacks{};
		for (auto possibleMove : forced->getCheckRoute()) {
			int c = move(possibleMove.first, possibleMove.second);	// cases
			if (c == 1) newMoves.emplace_back(pair{possibleMove, attackable(possibleMove)});
			else if (c == 2) newAttacks.emplace_back(possibleMove);
		}	// the piece can move only if the move still block the opposite piece from checking.
		moves = newMoves;
		attacks = newAttacks;
		forced = nullptr;
	}
	else {
		moves = vector<pair<pair<int,int>, vector<Piece *>>>{};
		attacks = vector<pair<int,int>>{};
	}
	checkRoute = vector<pair<int, int>>{};
	for (auto pos : getPos(x, y)){
		Piece * target = gameBoard->getPiece(pos.first, pos.second);
		if (! target) {
			moves.emplace_back(pair{pos, attackable(pos)});
		}
	}
}



/*
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