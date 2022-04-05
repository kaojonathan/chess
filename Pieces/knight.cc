#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "knight.h"
#include "../Board/board.h"
#include "../Players/player.h"
using namespace std;

Knight::Knight(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 3;
	representation = (side == 0) ? "N" : "n";
}

// return all positions the Knight at (col, row) can move to, not include positions out of bound 
vector<std::pair<int, int>> Knight::getPos(int col, int row) {
	vector<std::pair<int,int>> res{};
	for (int i = 1; i <= 2; i += 1){
		pair<int,int>curPos{col+i,row+(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
		curPos = pair<int, int>{col+i,row-(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
		curPos = pair<int, int>{col-i,row-(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
		curPos = pair<int, int>{col-i,row+(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
	}
	return res;
}

// return a vector of piece that the Knight at pos = (col, row) can capture
vector<Piece *> Knight::attackable(pair<int, int> position){
	vector<Piece *> res{};
	for (auto pos : getPos(position.first, position.second)){
		Piece *target = gameBoard->getPiece(pos.first, pos.second);
		if (target && side != target->getSide()) {
			res.emplace_back(target);
		}
	}
	return res;
}

// normal update
void Knight::nUpdate()  {
	updateStatus = 1;
	for (auto pos : getPos(x, y)){
		Piece * target = gameBoard->getPiece(pos.first, pos.second);
		if (target) {
			if (enemyKing(target)) {
				checkRoute.emplace_back(pair<int, int>{x,y});
				opponent->kingCheckedBy(this);
				targets.emplace_back(pos);
			}
			else if (side != target->getSide()) targets.emplace_back(pos);
			else protects.emplace_back(pos);
		}
		else {
			moves.emplace_back(pos);
		}
	}
}