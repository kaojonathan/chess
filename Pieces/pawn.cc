#include <string>
#include <vector>
#include <utility>
#include "pawn.h"
#include "../Board/board.h"
#include "../Players/player.h"
using namespace std;

// constructor
Pawn::Pawn(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 1; // change after the first move?
	representation = (side == 0) ? "P" : "p";
}

// forward one unit in the board
int Pawn::frDir(){ return (side == 0) ? -1 : 1; }

// return a list of piece that it can attack if it is at position at and not forced
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

// normal update
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
					else protects.emplace_back(pair<int, int>{sd,fr});
				}
			}
		}
	}
	fr += dir;
	if (numMoves == 0 && fr < 8 && fr >= 0 && !gameBoard->getPiece(x, fr))
		moves.emplace_back(pair<int, int>{x,fr});
}
