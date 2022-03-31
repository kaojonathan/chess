#include <iostream>
#include <string>
#include "piece.h"
#include "twoPlayerBoard.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
using namespace std;

twoPlayerBoard::twoPlayerBoard() {}
twoPlayerBoard::~twoPlayerBoard() {}
bool twoPlayerBoard::end() {}

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
	if (board[row][col])
	{
		delete board[row][col];
	}
	if (name == "K")
	{
		board[row][col] = new King{0, col, row, this};
	}
	else if (name == "k")
	{
		board[row][col] = new King{1, col, row, this};
	}
	else if (name == "Q")
	{
		board[row][col] = new Queen{0, col, row, this};
	}
	else if (name == "q")
	{
		board[row][col] = new Queen{1, col, row, this};
	}
	else if (name == "R")
	{
		board[row][col] = new Rook{0, col, row, this};
	}
	else if (name == "r")
	{
		board[row][col] = new Rook{1, col, row, this};
	}
	else if (name == "P")
	{
		board[row][col] = new Pawn{0, col, row, this};
	}
	else if (name == "p")
	{
		board[row][col] = new Pawn{1, col, row, this};
	}
	else if (name == "B")
	{
		board[row][col] = new Bishop{0, col, row, this};
	}
	else if (name == "b")
	{
		board[row][col] = new Bishop{1, col, row, this};
	}
	else if (name == "N")
	{
		board[row][col] = new Knight{0, col, row, this};
	}
	else if (name == "n")
	{
		board[row][col] = new Knight{1, col, row, this};
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

void twoPlayerBoard::set(int x, int y, Piece *p)
{
	board[y][x] = p;
}

bool twoPlayerBoard::verifySetup()
{ // uses the character matrix
	int numWhiteKings = 0;
	int numBlackKings = 0;

	Piece *whiteKing;
	Piece *blackKing;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (board[i][j])
			{

				// check one white and black king

				if (board[i][j]->getRep() == "k")
				{
					blackKing = board[i][j];
					++numBlackKings;
				}
				else if (board[i][j]->getRep() == "K")
				{
					whiteKing = board[i][j];
					++numWhiteKings;
				}

				// check no pawns on first or last row of board

				if (i == 0 || i == 7)
				{
					if (board[i][j]->getRep() == "P" || board[i][j]->getRep() == "p")
					{				  // if pawn exists on first or last row of board
						return false; // false
					}
				}
			}
		}
	}

	if (numWhiteKings != 1 || numBlackKings != 1)
	{

		return false;
	}
	else
	{ // if these conditions are satisfied

		// check if neither king is in check

		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{

				if (board[i][j])
				{

					if (board[i][j]->canAttack(std::pair<int, int>{whiteKing->getX(), whiteKing->getY()}))
					{
						return false;
					}
				}
			}
		}

		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{

				if (board[i][j])
				{

					if (board[i][j]->canAttack(std::pair<int, int>{blackKing->getX(), blackKing->getY()}))
					{
						return false;
					}
				}
			}
		}

		return true;
	}
}

void twoPlayerBoard::origSetup()
{

	board[0][0] = new Rook{1, 0, 0, this};
	board[0][1] = new Knight{1, 1, 0, this};
	board[0][2] = new Bishop{1, 2, 0, this};
	board[0][3] = new Queen{1, 3, 0, this};
	board[0][4] = new King{1, 4, 0, this};
	board[0][5] = new Bishop{1, 5, 0, this};
	board[0][6] = new Knight{1, 6, 0, this};
	board[0][7] = new Rook{1, 7, 0, this};

	for (int i = 0; i < 8; ++i)
	{
		board[1][i] = new Pawn{1, i, 1, this};
	}

	board[7][0] = new Rook{0, 0, 7, this};
	board[7][1] = new Knight{0, 1, 7, this};
	board[7][2] = new Bishop{0, 2, 7, this};
	board[7][3] = new Queen{0, 3, 7, this};
	board[7][4] = new King{0, 4, 7, this};
	board[7][5] = new Bishop{0, 5, 7, this};
	board[7][6] = new Knight{0, 6, 7, this};
	board[7][7] = new Rook{0, 7, 7, this};

	for (int i = 0; i < 8; ++i)
	{
		board[6][i] = new Pawn{0, i, 6, this};
	}
}
