#include <string>
#include <vector>
#include <iostream>
#include "piece.h"
#include "pawn.h"
#include "../Board/board.h"
#include "../Players/player.h"
using namespace std;

// constructor
Piece::Piece(int side, int x, int y, Board *board) : x{x},
													 y{y},
													 side{side},
													 updateStatus{0},
													 recent{false},
													 moves{vector<pair<int, int>>{}},
													 targets{vector<pair<int, int>>{}},
													 protects{vector<pair<int, int>>{}},
													 castle{vector<pair<int, int>>{}},
													 numMoves{0},
													 gameBoard{board} {}

// destructor
Piece::~Piece() {}

// set x, y fields
void Piece::setPos(int col, int row)
{
	x = col;
	y = row;
}

// field getters
string Piece::getRep() { return representation; }
int Piece::getSide() { return side; }

void Piece::attach(Board *board) { gameBoard = board; }


int Piece::getX() { return x; }

int Piece::getY() { return y; }

vector<pair<int, int>> Piece::getCheckRoute() { return checkRoute; }

int Piece::getVal() { return value; }

vector<pair<int, int>> Piece::getMoves() { return moves; }

vector<pair<int, int>> Piece::getTargets() { return targets; }

vector<pair<int, int>> Piece::getProtects() { return protects; }

void Piece::needsUpdate()
{
	updateStatus = 0;
	moves = vector<pair<int, int>>{};
	targets = vector<pair<int, int>>{};
	protects = vector<pair<int, int>>{};
	checkRoute = vector<pair<int, int>>{};
	castle = vector<pair<int, int>>{};
	forced = nullptr;
}

bool Piece::isKing()
{
	return representation == "k" || representation == "K";
}

bool Piece::enemyKing(Piece *target)
{
	if (target == nullptr)
	{
		return false;
	}
	else
	{
		return target->getSide() != side && target->isKing();
	}
}

// generate the paths with direction based on type:
//	1: diagonal directions only
//	2: cross directions only
//	3: both diagonal and cross directions
vector<pair<int, int>> getPos(int col, int row, int i, int type)
{
	vector<pair<int, int>> pos;
	if (type == 1 || type == 3)
	{
		pos.emplace_back(pair<int, int>{col + i, row + i}); // tr
		pos.emplace_back(pair<int, int>{col - i, row + i}); // tl
		pos.emplace_back(pair<int, int>{col + i, row - i}); // br
		pos.emplace_back(pair<int, int>{col - i, row - i}); // bl
	}
	if (type == 2 || type == 3)
	{
		pos.emplace_back(pair<int, int>{col, row + i}); // t
		pos.emplace_back(pair<int, int>{col, row - i}); // b
		pos.emplace_back(pair<int, int>{col + i, row}); // r
		pos.emplace_back(pair<int, int>{col - i, row}); // l
	}
	return pos;
}

// helper function that determines of the piece in position (x, y) checks the king
bool Piece::posInCheck(int col, int row)
{
	return !isKing() && enemyKing(mostVal(attackable(pair<int, int>{col, row})));
} // can I use this for computer level 2 and 3???

// return true if all int in dir are 0
bool checkEnd(vector<int> dir)
{
	for (auto j : dir)
	{
		if (j != 0)
			return false; // all paths end
	}
	return true;
}

// scan the paths with direction based on type, find all the enemy pieces that block each path (if any)
vector<Piece *> Piece::dScan(pair<int, int> at, int type)
{
	vector<Piece *> attackables;
	int ndir = (type == 3) ? 8 : 4; // number of directions
	vector<int> dir(ndir, 1);		// 0 means the path ends
	for (int i = 1; !checkEnd(dir); i += 1)
	{
		vector<pair<int, int>> pos = getPos(at.first, at.second, i, type); // all possible positions of this iteration
		for (int j = 0; j < ndir; j += 1)
		{ // loop on all directions
			// check if out of board
			if (!validPos(pos.at(j)))
				dir.at(j) = 0;
			// if the path has not end
			if (dir.at(j) > 0)
			{
				Piece *target = gameBoard->getPiece(pos.at(j).first, pos.at(j).second); // piece on the next position
				if (target)
				{ // if there is a piece
					if (target->getSide() != side)
					{ // put the enemy piece into attackables
						attackables.emplace_back(target);
					}
					dir.at(j) = 0; // this path ends
				}
			}
		}
	}
	return attackables;
}

// updating the moves, targets; notify the opponent if it is checking the king; notify the enemy piece if this is forcing the piece. (assuming this is not forced, all status fields are initially empty). Used for Bishop, Rook and Queen only.
void Piece::dirScan(int type)
{
	// scan all/some directions from {tr, tl, br, bl, t, b, r, l}, end if goes out of bound or enounters at lease 2 pieces (opposite) or enounters at lease 1 piece (mate), record each path
	int ndir = (type == 3) ? 8 : 4; // number of directions
	vector<int> dirs(ndir, 2);
	vector<vector<pair<int, int>>> paths(ndir, vector<pair<int, int>>{pair<int, int>{x, y}});
	vector<Piece *> firstEncounter(ndir, nullptr); // record the first enemy piece that block each path
	for (int i = 1; !checkEnd(dirs); i += 1)
	{
		vector<pair<int, int>> pos = getPos(x, y, i, type); // get all possible positions that the piece can go and i units away from the piece.
		for (int j = 0; j < ndir; j += 1)
		{ // loop on all directions
			// check if out of board
			pair<int, int> curPos{pos.at(j)};
			if (!validPos(curPos))
				dirs.at(j) = 0;
			else if (dirs.at(j) > 0)
			{
				Piece *target = gameBoard->getPiece(curPos.first, curPos.second); // piece on the next position
				if (dirs.at(j) == 2)
				{
					if (target)
					{ // if there is a piece on the position
						if (enemyKing(target))
						{
							// if the piece is the king of the enemy
							dirs.at(j) = 0;
							targets.emplace_back(curPos);
							checkRoute = paths.at(j);
							// notify the other player the king is checked
							//  in Player class, need a field Piece * enemyCheck and a set method checkBy(Piece)
							opponent->kingCheckedBy(this);
						}
						else if (target->getSide() != side)
						{
							// the piece is not king but belongs to enemy
							dirs.at(j) -= 1;
							targets.emplace_back(pos.at(j));
							paths.at(j).emplace_back(curPos);
							firstEncounter.at(j) = target;
						}
						else
						{ // blocked by mate, path stops
							protects.emplace_back(pos.at(j));
							dirs.at(j) = 0;
						}
					}
					else
					{ //  no piece on that position
						if (!forced)
							moves.emplace_back(curPos);
						paths.at(j).emplace_back(curPos);
					} // no block
				}
				else if (dirs.at(j) == 1)
				{ // has past an enemy piece
					if (target)
					{
						// meet the second piece
						if (enemyKing(target))
						{
							// will check the king if the enemy piece here moves.
							checkRoute = paths.at(j);
							firstEncounter.at(j)->forcedBy(this); // update the status of the forced piece.
						}
						dirs.at(j) = 0;
					}
					else
					{
						paths.at(j).emplace_back(curPos);
					}
				}
			}
		}
	}
}

// return the validity of an attempt to move:
//  0: not valid (not protect)
//	1: valid move
//	2: valid capture
//  3: valid castle
//  4: valid promotion (no capture)
//  5: valid promotion (capture)
//  6: enPassant valid
int Piece::move(int col, int row)
{
	for (auto mv : moves)
	{
		if (mv.first == col && mv.second == row)
		{
			if (representation == "P" && row == 0)
			{ // promotion condition
				return 4;
			}
			else if (representation == "p" && row == 7)
			{
				return 4;
			}
			else
			{
				return 1;
			}
		}
	}
	for (auto pos : targets)
	{
		if (pos.first == col && pos.second == row)
		{
			if (representation == "P" && row == 0)
			{ // promotion condition
				return 5;
			}
			else if (representation == "p" && row == 7)
			{
				return 5;
			}
			else
			{
				return 2;
			}
		}
	}	

	// castling condition
	if (this->getRep() == "K")
	{
		if (this->numMoves == 0)
		{
			if ((col == 6) && (row == 7))
			{
				if (gameBoard->getPiece(7, 7))
				{
					Piece *castler = gameBoard->getPiece(7, 7); // castler
					if (castler->getRep() == "R" && castler->numMoves == 0)
					{ // rook there and didnt move
						if (!gameBoard->getPiece(6, 7) && !gameBoard->getPiece(5, 7))
						{ // no pieces in between
							for (int i = 0; i < 8; i++)
							{
								for (int j = 0; j < 8; j++)
								{
									if (gameBoard->getPiece(i, j))
									{

										Piece *potentialAttacker = gameBoard->getPiece(i, j);

										if (potentialAttacker->getSide() == 1)
										{

											if (!potentialAttacker->canAttack(pair<int, int>{4, 7}) && !potentialAttacker->canAttack(pair<int, int>{5, 7}) && !potentialAttacker->canAttack(pair<int, int>{6, 7}))
											{ // king not in check in between
												return 3;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else if ((col == 2) && (row == 7))
			{

				if (gameBoard->getPiece(0, 7))
				{
					Piece *castler = gameBoard->getPiece(0, 7); // castler
					if (castler->getRep() == "R" && castler->numMoves == 0)
					{ // rook there and didnt move
						if (!gameBoard->getPiece(1, 7) && !gameBoard->getPiece(2, 7) && !gameBoard->getPiece(3, 7))
						{ // no pieces in between
							for (int i = 0; i < 8; i++)
							{
								for (int j = 0; j < 8; j++)
								{
									if (gameBoard->getPiece(i, j))
									{

										Piece *potentialAttacker = gameBoard->getPiece(i, j);

										if (potentialAttacker->getSide() == 1)
										{

											if (!potentialAttacker->canAttack(pair<int, int>{2, 7}) && !potentialAttacker->canAttack(pair<int, int>{3, 7}) && !potentialAttacker->canAttack(pair<int, int>{4, 7}))
											{ // king not in check in between
												return 3;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (this->getRep() == "k")
	{
		if (this->numMoves == 0)
		{
			if ((col == 6) && (row == 0))
			{

				if (gameBoard->getPiece(7, 0))
				{
					Piece *castler = gameBoard->getPiece(7, 0); // castler
					if (castler->getRep() == "r" && castler->numMoves == 0)
					{ // rook there and didnt move
						if (!gameBoard->getPiece(6, 0) && !gameBoard->getPiece(5, 0))
						{ // no pieces in between
							for (int i = 0; i < 8; i++)
							{
								for (int j = 0; j < 8; j++)
								{
									if (gameBoard->getPiece(i, j))
									{

										Piece *potentialAttacker = gameBoard->getPiece(i, j);

										if (potentialAttacker->getSide() == 0)
										{

											if (!potentialAttacker->canAttack(pair<int, int>{4, 0}) && !potentialAttacker->canAttack(pair<int, int>{5, 0}) && !potentialAttacker->canAttack(pair<int, int>{6, 0}))
											{ // king not in check in between
												return 3;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else if ((col == 2) && (row == 0))
			{
				if (gameBoard->getPiece(0, 0))
				{
					Piece *castler = gameBoard->getPiece(0, 0); // castler
					if (castler->getRep() == "r" && castler->numMoves == 0)
					{ // rook there and didnt move
						if (!gameBoard->getPiece(1, 0) && !gameBoard->getPiece(2, 0) && !gameBoard->getPiece(3, 0))
						{ // no pieces in between
							for (int i = 0; i < 8; i++)
							{
								for (int j = 0; j < 8; j++)
								{
									if (gameBoard->getPiece(i, j))
									{

										Piece *potentialAttacker = gameBoard->getPiece(i, j);

										if (potentialAttacker->getSide() == 0)
										{

											if (!potentialAttacker->canAttack(pair<int, int>{2, 0}) && !potentialAttacker->canAttack(pair<int, int>{3, 0}) && !potentialAttacker->canAttack(pair<int, int>{4, 0}))
											{ // king not in check in between
												return 3;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (this->getRep() == "P")
	{
		if (col == this->x + 1)
		{
			if (row == this->y - 1)
			{
				if (gameBoard->getPiece(this->x + 1, this->y))
				{
					Piece *e = gameBoard->getPiece(this->x + 1, this->y);
					if (e->getRep() == "p")
					{
						if (e->getRecent()) // recent pawn that moved two
						{
							// perform enPassant

							return 6;
						}
					}
				}
			}
		}
		else if (col == this->x - 1)
		{
			if (row == this->y - 1)
			{

				if (gameBoard->getPiece(this->x - 1, this->y))
				{
					Piece *e = gameBoard->getPiece(this->x - 1, this->y);
					if (e->getRep() == "p")
					{
						if (e->getRecent()) // recent pawn that moved two
						{
							// perform enPassant

							return 6;
						}
					}
				}
			}
		}
	}
	else if (this->getRep() == "p")
	{

		if (col == this->x + 1)
		{
			if (row == this->y + 1)
			{
				if (gameBoard->getPiece(this->x + 1, this->y))
				{
					Piece *e = gameBoard->getPiece(this->x + 1, this->y);
					if (e->getRep() == "P")
					{
						if (e->getRecent()) // recent pawn that moved two
						{
							// perform enPassant

							return 6;
						}
					}
				}
			}
		}
		else if (col == this->x - 1)
		{
			if (row == this->y + 1)
			{

				if (gameBoard->getPiece(this->x - 1, this->y))
				{
					Piece *e = gameBoard->getPiece(this->x - 1, this->y);
					if (e->getRep() == "P")
					{
						if (e->getRecent()) // recent pawn that moved two
						{
							// perform enPassant

							return 6;
						}
					}
				}
			}
		}
	}

	return 0;
}

// get the number of moves on this piece
int Piece::getNumMoves()
{
	return numMoves;
}

// ++numMoves
void Piece::incNumMoves()
{
	++numMoves;
}

// update a piece that is forced by enemPiece
void Piece::fUpdate(Piece *enemyPiece)
{
	updateStatus = 2;
	vector<pair<int, int>> newMoves{};
	vector<pair<int, int>> newtargets{};
	protects = vector<pair<int, int>>{};
	for (auto possibleMove : forced->getCheckRoute())
	{
		int c = move(possibleMove.first, possibleMove.second);
		if (c == 1 || c == 3 || c == 4)
			newMoves.emplace_back(possibleMove);
		else if (c == 2 || c == 5 || c == 6)
			newtargets.emplace_back(possibleMove);
	} // the piece can move only if the move still block the opposite piece from checking.
	moves = newMoves;
	targets = newtargets;
}

// update status field, notify any enemy piece when forcing it, or notify the opponent when this piece is checking the king.
void Piece::statusUpdate()
{
	if (updateStatus == 0)
		nUpdate();
}

// update moves and targets field of a piece that is forced by enemyPiece
void Piece::forcedBy(Piece *enemyPiece, bool check)
{
	forced = enemyPiece;
	statusUpdate();
	if (updateStatus == 1 || check)
		fUpdate(enemyPiece);
}


// return true if this Piece can attack the enemy piece in position (col, row) (regardness the existence of the piece)
bool Piece::canAttack(pair<int, int> pos)
{
	Pawn *p = dynamic_cast<Pawn *>(this);
	if (p) {
		return (pos.first == x + 1 || pos.first == x - 1) && pos.second == y + p->frDir() && !forced;
	}
	cout << "piece: " << representation << endl;
	for (auto pt : protects) {
		if (pt.first == pos.first && pt.second == pos.second) 
			return true;
	} 
	int moveStatus = move(pos.first, pos.second);
	return moveStatus == 1 || moveStatus == 2;
}

void Piece::setOpponent(Player *o)
{
	opponent = o;
}

bool Piece::isUpdated()
{
	return updateStatus != 0;
}

// return the most valuable Piece from a vector of Pieces, nullptr if the vector is empty
//   comment: can be further changed to handle gain and cost with the guard field (not implemented yet)
Piece *mostVal(vector<Piece *> attackables)
{
	Piece *res = nullptr;
	for (auto enemy : attackables)
	{
		if (res)
		{
			if (enemy->getVal() > res->getVal())
				res = enemy;
		}
		else
		{
			res = enemy;
		}
	}
	return res;
}

// true if the position is not out of the board
bool Piece::validPos(pair<int, int> pos)
{
	return !(pos.first >= 8 || pos.second >= 8 || pos.first < 0 || pos.second < 0);
}

void Piece::setRecent()
{
	recent = true;
}

void Piece::resetRecent()
{
	recent = false;
}

bool Piece::getRecent()
{
	return recent;
}