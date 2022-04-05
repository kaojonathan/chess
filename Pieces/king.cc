#include <string>
#include <vector>
#include <utility>
#include "king.h"
#include "../Board/board.h"
#include "rook.h"
#include "../Players/player.h"
using namespace std;

// constructor
King::King(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 10;
	representation = (side == 0) ? "K" : "k";
}

// get all basic positions on the board that the king can move to, don't check if the move is valid or not
vector<pair<int,int>> King::getPos(int col, int row){
	pair<int, int> ybound {(side == 0) ? pair<int,int> {5, 8} : pair<int,int>{0, 3}};
	vector<pair<int,int>> res {};
	for (int m = -1; m <= 1; m += 1 ) {
		if (col + m < 0 || col + m >= 8) continue;
		if (row + 1 >= ybound.first && row + 1 < ybound.second)  res.emplace_back(pair<int,int> {col + m, row + 1});
		if (row - 1 >= ybound.first && row - 1 < ybound.second)  res.emplace_back(pair<int,int> {col + m, row - 1});
		if (m != 0) res.emplace_back(pair<int,int> {col + m, row});
	}
	return res;
}

// return a vector of Piece that can be attacked by King if king is at position at
vector<Piece *> King::attackable(pair<int, int> at){
	vector<pair<int, int>> possibleMoves = getPos(at.first, at.second);	// all spaces around it
	vector<Piece *> res {};
	for (auto pos : possibleMoves){ 
		Piece *target = gameBoard->getPiece(pos.first, pos.second);
		if (target && side != target->getSide()) res.emplace_back(target);
	}
	return res;
}

// normal update
void King::nUpdate() {
	vector<pair<int, int>> possibleMoves = getPos(x, y);
	for (auto pos : possibleMoves){
		// basic valid position
		if (opponent->canAttack(pos).size() > 0){
			continue;
		} // if pos not in the board or in the attack range of the opponent (not implemented)
		Piece *target = gameBoard->getPiece(pos.first, pos.second);
		if (target){
			if (side != target->getSide())
				targets.emplace_back(pos); 
			else protects.emplace_back(pos);
		}
		else moves.emplace_back(pos);
	}
}
