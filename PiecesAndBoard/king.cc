#include <string>
#include <vector>
#include <utility>
#include "king.h"
#include "board.h"
using namespace std;


King::King(bool isWhite) : Piece{ isWhite } {
	value = 10;
	if (isWhite) {
		representation = "K";
	}
	else {
		representation = "k";
	}
}

King::~King() {
}

// return a vector of Piece that can be attacked by King if king is at position at
vector<Piece *> King::attackable(pair<int, int> at){
	vector<pair<int, int>> possibleMoves = getPos(at.first, at.second, 1, 3);
	vector<pair<int, int>> res {};
	for (auto pos : possibleMoves){
		// basic valid position
		if (pos.second > 3 || pos.second < 0 || pos.first < 0 || pos.second > 8){
			continue;
		}
		Piece *target = gameBoard->getPiece(pos.first, pos.second);
		if (target && side != target->getSide()) {
			res.emplace_back(target);
		}
	}
}


void King::updateMovePossibilities() {
	vector<pair<int, int>> possibleMoves = getPos(x, y, 1, 3);
	for (auto pos : possibleMoves){
		// basic valid position
		if (pos.second > 3 || pos.second < 0 || pos.first < 0 || pos.second > 8){
			continue;
		}
		// if pos not in the attack range of the enemy (not implemented)
		Piece *target = gameBoard->getPiece(pos.first, pos.second);
		if (false){ 
			// not implemented, if this position can be attacked by an enemy

		}
		else if (target){
			if (side != target->getSide()) {
				attacks.emplace_back(target); 
			}
		}
		else moves.emplace_back(pair{pos, attackable(pos)}); 
	}
}


/* pair<int, int> King::getCheckCoords() { return pair<int,int>{};} */