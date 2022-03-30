#include <string>
#include <vector>
#include "piece.h"
#include "board.h"
<<<<<<< HEAD
#include "../players/player.h"
=======
#include "../Players/player.h"
>>>>>>> 3af86c7f85ca405a58971bbcffe14f119919c7fd
using namespace std;

Piece::Piece(int side, int x, int y, Board * board) : x{x}, y{y}, side{side}, updateStatus{0}, DNA{0} {
	board->set(x, y, this);
}

void Piece::setPos(int col, int row) {
	x = col;
	y = row;
}

string Piece::getRep() { return representation; }

void Piece::attach(Board* board) { gameBoard = board; }

// 0: white, 1: black
int Piece::getSide() { return side; }

int Piece::getX() { return x; }

int Piece::getY() { return y; }


vector<pair<int,int>> Piece::getCheckRoute() { return checkRoute; }

int Piece::getVal(){ return value; }

vector<pair<int,int>> Piece::getMoves(){ return moves; }

vector<pair<int,int>> Piece::getTargets(){ return targets; }

void Piece::needsUpdate() { 
	updateStatus = 0;
	moves = vector<pair<int,int>> {};
	targets = vector<pair<int,int>> {};
	checkRoute = vector<pair<int,int>> {};
	forced = nullptr;
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
	return !isKing() && enemyKing(mostVal(attackable(pair<int, int>{col, row})));
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
			if (!validPos(pos.at(j))) dir.at(j) = 0;
			// if the path has not end
			if (dir.at(j) > 0) {
				Piece * target = gameBoard->getPiece(pos.at(j).first, pos.at(j).second); // piece on the next position
				if (target) {	// if there is a piece
					if (target->getSide() != side) {	// put the enemy piece into attackables
						attackables.emplace_back(target);
					}
					dir.at(j) = 0;	// this path ends
				}
			}
		}
	}
	return attackables;
}

// updating the moves, targets; notify the opponent if it is checking the king; notify the enemy piece if this is forcing the piece. (assuming this is not forced, all status fields are initially empty). Used for Bishop, Rook and Queen only. 
void Piece::dirScan(int type) {
	// scan all/some directions from {tr, tl, br, bl, t, b, r, l}, end if goes out of bound or enounters at lease 2 pieces (opposite) or enounters at lease 1 piece (mate), record each path
	int ndir = (type == 3) ? 8 : 4; // number of directions
	vector<int> dirs(ndir, 2);
	vector<vector<pair<int,int>>> paths(ndir, vector<pair<int,int>>{pair<int,int>{x,y}});	
	vector<Piece*> firstEncounter(ndir, nullptr); // record the first enemy piece that block each path
	for (int i = 1; !checkEnd(dirs); i += 1){
		vector<pair<int, int>> pos = getPos(x, y, i, type); // get all possible positions that the piece can go and i units away from the piece. 
		for (int j = 0; j < ndir; j += 1){	// loop on all directions
			// check if out of board
			pair<int,int>curPos{pos.at(j)}; 
			if (!validPos(curPos)) dirs.at(j) = 0;
			else if (dirs.at(j) > 0) {
				Piece * target = gameBoard->getPiece(curPos.first, curPos.second); // piece on the next position
				if (dirs.at(j) == 2){
					if(target) {	// if there is a piece on the position
						if (enemyKing(target)) {
							// if the piece is the king of the enemy
							dirs.at(j) = 0;
							targets.emplace_back(curPos);
							checkRoute = paths.at(j);
							//notify the other player the king is checked
							// in Player class, need a field Piece * enemyCheck and a set method checkBy(Piece) 
							enemy->kingCheckedBy(this);
						}
						else if (target->getSide() != side){
							// the piece is not king but belongs to enemy
							dirs.at(j) -= 1;
							targets.emplace_back(pos.at(j));
							paths.at(j).emplace_back(curPos);
							firstEncounter.at(j) = target;
						}
						else {// blocked by mate, path stops
							dirs.at(j) = 0;
						}
					}
					else {	//  no piece on that position
							if (!forced) moves.emplace_back(curPos);
							paths.at(j).emplace_back(curPos);
					} 	// no block
				}
				else if (dirs.at(j) == 1) {	// has past an enemy piece
					if (target) {
						// meet the second piece
						if (enemyKing(target)) {
							// will check the king if the enemy piece here moves.
							checkRoute = paths.at(j);
							firstEncounter.at(j)->forcedBy(this);  // update the status of the forced piece.
						}
						dirs.at(j) == 0;	
					}
					else {
						paths.at(j).emplace_back(curPos);
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
		if (mv.first == col && mv.first == row) return 1;
	}
	for (auto pos : targets){
		if (pos.first = col && pos.second == row) return 2;
	}
	return 0;
}

// update a piece that is forced by enemPiece
void Piece::fUpdate(Piece * enemyPiece){
	updateStatus = 2;
	vector<pair<int,int>> newMoves{};
	vector<pair<int,int>> newtargets{};
	for (auto possibleMove : forced->getCheckRoute()) {
		int c = move(possibleMove.first, possibleMove.second);
		if (c == 1) newMoves.emplace_back(possibleMove);
		else if (c == 2) newtargets.emplace_back(possibleMove);
	}	// the piece can move only if the move still block the opposite piece from checking.
	moves = newMoves;
	targets = newtargets;
}

// update status field, notify any enemy piece when forcing it, or notify the opponent when this piece is checking the king.
void Piece::statusUpdate() {
	if (updateStatus == 0) nUpdate();
}

// update moves and targets field of a piece that is forced by enemyPiece
void Piece::forcedBy(Piece * enemyPiece, bool check) {
	forced = enemyPiece;
	statusUpdate();
	if (updateStatus == 1 || check) fUpdate(enemyPiece);
}


// return true if this piece is checking the enemy king
/*bool Piece::kingCheck() {
	return checkRoute.size() != 0;
}*/

// return true if this Piece can attack the enemy piece in position (col, row) (regardness the existence of the piece)
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

// true if the position is not out of the board
bool Piece::validPos(pair<int, int> pos){
	return !(pos.first >= 8 || pos.second >= 8 || pos.first < 0 || pos.second < 0);
}
