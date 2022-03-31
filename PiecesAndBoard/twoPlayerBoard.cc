#include <iostream>
#include <string>
#include "piece.h"
#include "twoPlayerBoard.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
using namespace std;

twoPlayerBoard::twoPlayerBoard() {}
twoPlayerBoard::~twoPlayerBoard() {}
bool twoPlayerBoard::end() {};

Piece *twoPlayerBoard::getP(int x, int y)
{
	return board[y][x];
}

// returns true of the (x, y) position is in the board
bool twoPlayerBoard::validPos(int x, int y)
{
	return 0 <= x && 0 <= y && x <= 8 && y <= 8;
}

void twoPlayerBoard::movePiece(int x, int y, int newx, int newy)
{ 
	// check if piece is null
	if (board[y][x])
	{

		int result = board[y][x]->move(newx, newy);

		if (result == 2)
		{

			if ((("a" <= board[y][x]->getRep()) &&
				 (board[y][x]->getRep() <= "z")) &&
				(("A" <= board[newy][newx]->getRep()) &&
				 (board[newy][newx]->getRep() <= "Z")))
			{

		

				board[newy][newx] = board[y][x];
				board[y][x] = nullptr;
				board[newy][newx]->setPos(newy, newx);
			}
			else if ((("A" <= board[y][x]->getRep()) &&
					  (board[y][x]->getRep() <= "Z")) &&
					 (("a" <= board[newy][newx]->getRep()) &&
					  (board[newy][newx]->getRep() <= "z")))
			{

				board[newy][newx] = board[y][x];
				board[y][x] = nullptr;
				board[newy][newx]->setPos(newy, newx);
			}

		}
		else if (result == 1)
		{

			board[newy][newx] = board[y][x];
			board[y][x] = nullptr;
			board[newy][newx]->setPos(newy, newx);

		}
		else if (result == 0)
		{

			// do nothing
		}
	}
}


// move to interface
void twoPlayerBoard::print()
{
	for (int i = 0; i < 8; ++i)
	{
		cout << 8 - i << ' ';
		for (int j = 0; j < 8; ++j)
		{
			if (board[i][j] == nullptr)
			{ // empty tile
				if ((i + j) % 2)
				{ // if sum is odd it's a white tile
					cout << '_';
				}
				else
				{ // otherwise it's a black tile

					cout << ' ';
				}
			}
			else
			{ // piece is on it
				cout << board[i][j]->getRep();
			}
		}
		cout << endl;
	}
	cout << endl
		 << "  ";
	for (int i = 0; i < 8; ++i)
	{

		char s = 'a' + i;
		cout << s;
	}
	cout << endl;
}


void twoPlayerBoard::insertNewPiece(string name, string position)
{
	int row = 8 - (position[1] - '0');
	int col = position[0] - 'a';
	if (board[row][col]) {
		delete board[row][col];
	}
	if (name == "K") {
		new King{1, col, row, this};
	} else if (name == "k") {
		new King{0, col, row, this};
	} else if (name == "Q") {
		new Queen{0, col, row, this};
	} else if (name == "q") {
		new Queen{0, col, row, this};
	} else if (name == "R") {
		new Rook{0, col, row, this};
	} else if (name == "r") {
		new Rook{0, col, row, this};
	} else if (name == "P") {
		new Pawn{0, col, row, this};
	} else if (name == "p") {
		new Pawn{0, col, row, this};
	} else if (name == "B") {
		new Bishop{0, col, row, this};
	} else if (name == "b") {
		new Bishop{0, col, row, this};
	} else if (name == "N") {
		new Knight{0, col, row, this};
	} else if (name == "n") {
		new Knight{0, col, row, this};
	}
}

void twoPlayerBoard::removePiece(string position)
{
	int row = 8 - (position[1] - '0');
	int col = position[0] - 'a';
	if (board[row][col])
	{
		delete board[row][col];
	}
}

void twoPlayerBoard::set(int x, int y, Piece * p) {
	board[y][x] = p;
}
