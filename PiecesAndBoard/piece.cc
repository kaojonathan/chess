#include <string>
#include <vector>
#include "piece.h"
#include "board.h"
using namespace std;

Piece::Piece(bool isWhite) : side{isWhite ? 0 : 1} {}

void Piece::setPos(int col, int row) {
	x = col;
	y = row;
}

string Piece::getRep() {
	return representation;
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

int Piece::getVal(){
	return value;
}

void Piece::forcedBy(Piece * enemyPiece) {
	forced = enemyPiece;
}

bool Piece::isKing(){
	return representation == "k" || representation == "K";
}

bool Piece::enemyKing(Piece * target) {
	return target->getSide() != side && target->isKing();
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

// helper function that determines of the piece in position (x, y) checks the king
bool Piece::posInCheck(int col, int row) {
	return !isKing() && enemyKing(mostVal(attackable(pair{col, row})));
}

// return true if all int in dir are 0
bool checkEnd(vector<int> dir){
	for (auto j : dir) {
			if (j != 0) return false;	// all paths end
	}
	return true;
}

// scan the paths with direction based on type, find all the enemy pieces that block each path (if any)
vector<Piece *> Piece::dScan(pair<int, int> at, int type){
	vector <Piece *> attackables;
	int ndir = (type == 3) ? 8 : 4; // number of directions
	vector<int> dir(ndir, 1);		// 0 means the path ends
	for (int i = 1; !checkEnd(dir); i += 1){
		vector<pair<int,int>> pos = getPos(at.first, at.second, i, type); // all possible positions of this iteration
		for (int j = 0; j < ndir; j += 1){	// loop on all directions
			// check if out of board
			if (pos.at(j).first > 8 || pos.at(j).second > 8 || pos.at(j).first < 0 || pos.at(j).second < 0) dir.at(j) = 0;
			// if the path has not end
			if (dir.at(j) > 0) {
				Piece * target = gameBoard->getPiece(pos.at(j).first, pos.at(j).second); // piece on the next position
				if (target) {	// if there is a piece
					if (target->getSide() != side) {// put the enemy piece into attackables
						attackables.emplace_back(target);
					}
					dir.at(j) = 0;	// this path ends
				}
			}
		}
	}
	return attackables;
}


void Piece::updateStatus(int type) {
	// check if the piece cannot move because the enemy piece threaten
	if (forced) {
		vector<pair<pair<int,int>, vector<Piece*>>> newMoves{};
		vector<pair<int,int>> newAttacks{};
		for (auto possibleMove : forced->getCheckRoute()) {
			int c = move(possibleMove.first, possibleMove.second);
			if (c == 1) newMoves.emplace_back(pair{possibleMove, dScan(possibleMove, type)});
			else if (c == 2) newAttacks.emplace_back(possibleMove);
		}	// the piece can move only if the move still block the opposite piece from checking.
		moves = newMoves;
		attacks = newAttacks;
		forced = nullptr;
	}
	else {
		moves = vector<pair<pair<int,int>, vector<Piece *>>>{};
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
						if (enemyKing(target)) {
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
						else {// blocked by mate, path stops
							dir.at(j) = 0;
							// add this to target's guard field
							// problem: how to remove it when this is no more the guard of the target?

						}
					}
					else {	//  no piece on that position
							if (!forced) moves.emplace_back(pair{pos.at(j), dScan(pos.at(j), type)});
							paths.at(j).emplace_back(pos.at(j));
					} 	// no block
				}
				else if (dir.at(j) == 1) {	// has past a enemy piece
					if (target) {
						// meet the second piece
						if (enemyKing(target)) {
							// the piece will check the king if there is no block, but there is 
							checkRoute = paths.at(j);
							firstEncounter[j]->forcedBy(this);
						}
						dir.at(j) == 0;	
					}
					else {
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
	for (auto mv : moves) {
		if (mv.first.first == col && mv.first.first == row) return 1;
	}
	for (auto pos : attacks){
		if (pos.first = col && pos.second == row) return 2;
	}
	return 0;
}

// update moves
void Piece::updateMoves() {
    updateMovePossibilities();	
}

// return true if this piece is checking the enemy king
bool Piece::kingCheck() {
	return checkRoute.size() != 0;
}

// return true if this Piece can attack the enemy piece in position (col, row) (regardness the existence of the piece), used by queen, rook, bishop, knight, and king.
bool Piece::canAttack(pair<int, int> pos){
	return move(pos.first, pos.second) == 2;
}


// return the most valuable Piece from a vector of Pieces, nullptr if the vector is empty
//   comment: can be further changed to handle gain and cost with the guard field (not implemented yet)
Piece *mostVal(vector<Piece *> attackables){
	Piece * res = nullptr;
	for (auto enemy : attackables) {
		if (enemy->getVal() > res->getVal()) res = enemy;
	}
	return res;
} 