#include <string>
#include <vector>
#include "piece.h"
#include "board.h"
using namespace std;

Piece::Piece(bool isWhite) : side{isWhite ? 0 : 1} {}

void Piece::setPos(int row, int col) {
	x = row;
	y = col;
}

string Piece::getRep() {
	return representation;
}

bool Piece::isKing() {
	return (representation == "K" || representation == "k");
}

void Piece::attach(Board* board) {
	gameBoard = board;
}

// 0: white, 1: black
int Piece::getSide() {
	return side;
}

int Piece::getX() {
	return x;
}

int Piece::getY() {
	return y;
}


vector<pair<int,int>> Piece::getCheckRoute() { return checkRoute; }

void Piece::forcedBy(Piece * enemyPiece) {
	forced = enemyPiece;
}

int Piece::getVal(){
	return value;
}

// generate the paths with direction based on type: 
//	1: diagonal directions only
//	2: cross directions only
//	3: both diagonal and cross directions
vector<pair<int, int>> getPos(int col, int row, int i, int type){
	vector<pair<int, int>> pos;
	if (type == 1 || type == 3){
		pos.emplace_back(pair<int,int>{col+i, row+i});		//tr
		pos.emplace_back(pair<int,int>{col-i, row+i});		//tl			
		pos.emplace_back(pair<int,int>{col+i, row-i});		//br
		pos.emplace_back(pair<int,int>{col-i, row-i});		//bl
	}
	if (type == 2 || type == 3){
		pos.emplace_back(pair<int,int>{col, row+i});		//t	
		pos.emplace_back(pair<int,int>{col, row-i});		//b
		pos.emplace_back(pair<int,int>{col+i, row});		//r
		pos.emplace_back(pair<int,int>{col-i, row});		//l
	}
	return pos;
}

// return true if all int in dir are 0
bool checkEnd(vector<int> dir){
	for (auto j : dir) {
			if (j != 0) return false;	// all paths end
	}
	return true;
}

// scan the paths with direction based on type, find the most variable enemy piece the block one path
Piece* Piece::dScan(int col, int row, int type){
	Piece *res = nullptr;
	int ndir = (type == 3) ? 8 : 4; // number of directions
	vector<int> dir(ndir, 1);		// 0 means the path ends
	for (int i = 1; !checkEnd(dir); i += 1){
		vector<pair<int,int>> pos = getPos(col, row, i, type); // all possible pos of this iteration
		for (int j = 0; j < ndir; j += 1){	// loop on all directions
			// check if out of board
			if (pos.at(j).first > 8 || pos.at(j).second > 8 || pos.at(j).first < 0 || pos.at(j).second < 0) dir.at(j) = 0;
			// if the path has not end
			if (dir.at(j) > 0) {
				Piece * target = gameBoard->getPiece(pos.at(j).first, pos.at(j).second); // piece on the next position
				if (target) {	// if there is a piece
					if (target->getSide() != side) // pick the most valuable enemy piece that the target can capture
						res = (!res || res->getVal() < target->getVal()) ? target : res;
					dir.at(j) = 0;	// this path ends
				}
			}
		}
	}
	return res;
}


void Piece::updateStatus(int type) {
	// check if the piece cannot move because the enemy piece threaten
	if (forced) {
		vector<pair<int,int>> newMoves{};
		vector<pair<int,int>> newAttacks{};
		for (auto possibleMove : forced->getCheckRoute()) {
			int c = move(possibleMove.first, possibleMove.second);
			if (c == 1) newMoves.emplace_back(possibleMove);
			else if (c == 2) newAttacks.emplace_back(possibleMove);
		}	// the piece can move only if the move still block the opposite piece from checking.
		moves = newMoves;
		attacks = newAttacks;
		forced = nullptr;
	}
	else {
		moves = vector<pair<int,int>>{};
		attacks = vector<pair<int,int>>{};
	} 	// clean
	checkRoute = vector<pair<int,int>>{};

	// scan all/some directions from {tr, tl, br, bl, t, b, r, l}, end if goes out of bound or enounters at lease 2 pieces (opposite) or enounters at lease 1 piece (mate), record each path
	int ndir = (type == 3) ? 8 : 4; // number of directions
	vector<int> dir(ndir, 2);
	vector<vector<pair<int,int>>> paths(ndir, vector<pair<int,int>>{pair<int,int>{x,y}});	
	vector<Piece*> firstEncounter(ndir, nullptr); // record the first enemy piece that block each path
	for (int i = 1; !checkEnd(dir); i += 1){
		vector<pair<int, int>> pos = getPos(x, y, i, type);
		for (int j = 0; j < ndir; j += 1){	// loop on all directions
			// check if out of board
			if (pos.at(j).first > 8 || pos.at(j).second > 8 || pos.at(j).first < 0 || pos.at(j).second < 0) dir.at(j) = 0;
			if (dir.at(j) > 0) {
				Piece * target = gameBoard->getPiece(pos.at(j).first, pos.at(j).second); // piece on the next position
				if (dir.at(j) == 2){
					if(target) {	// if there is a piece on the position
						if (target->isKing() && target->getSide() != side) {
							// if the piece is the king of the enemy
							dir.at(j) = 0;
							attacks.emplace_back(pos.at(j));
							checkRoute = paths.at(j);
							//notify the other player the king is checked (incompleted)


						}
						else if (target->getSide() != side){
							// the piece is not king but belongs to enemy
							if (!forced) attacks.emplace_back(pos.at(j));
							dir.at(j) -= 1;
							paths.at(j).emplace_back(pos.at(j));
							firstEncounter.at(j) = target;
						}
						else // blocked by mate, path stops
							dir.at(j) = 0;
					}
					else {	//  no piece on that position
							if (!forced) moves.emplace_back(pos.at(j));
							paths[j].emplace_back(pos.at(j));
					} 	// no block
				}
				else if (dir.at(j) == 1) {	// has past a enemy piece
					if (target) {
						// meet the second piece
						if (target->getSide() != side && target->isKing()) {
							// the piece will check the king if there is no block, but there is 
							checkRoute = paths.at(j);
							firstEncounter[j]->forcedBy(this);
						}
						dir.at(j) == 0;	
					}
					else {
						if (!forced) moves.emplace_back(pos.at(j));
						paths.at(j).emplace_back(pos.at(j));
					}
				}
			}
		}
	}
}

// return the validity of an attempt to move:
//  0: not valid
//	1: valid move
//	2: valid capture
int Piece::move(int col, int row){
	for (auto pos : moves) {
		if (pos.first == col && pos.second == row) return 1;
	}
	for (auto pos : attacks){
		if (pos.first == col && pos.second == row) return 2;
	}
	return 0;
}


bool Piece::kingInCheck() {
	return checkRoute.size() != 0;
}
