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
{ // setter

	if ((board[y][x]->getRep() == "n") || (board[y][x]->getRep() == "N") ||
		(board[y][x]->getRep() == "b") || (board[y][x]->getRep() == "B") ||
		(board[y][x]->getRep() == "r") || (board[y][x]->getRep() == "R") ||
		(board[y][x]->getRep() == "q") || (board[y][x]->getRep() == "Q") ||
		(board[y][x]->getRep() == "p") || (board[y][x]->getRep() == "P") ||
		(board[y][x]->getRep() == "k") || (board[y][x]->getRep() == "K"))
	{

		int result = board[y][x]->move(newx, newy);

		if (result == 2)
		{

			if ((("a" <= board[y][x]->getRep()) &&
				 (board[y][x]->getRep() <= "z")) &&
				(("A" <= board[newy][newx]->getRep()) &&
				 (board[newy][newx]->getRep() <= "Z")))
			{

				delete board[newy][newx]; // we can make it track the number of pieces left by making the destructor body decrement a field. (I didn't implement yet)

				board[newy][newx] = board[y][x];
				board[y][x] = nullptr;
				board[newy][newx]->setPos(newy, newx);
			}
			else if ((("A" <= board[y][x]->getRep()) &&
					  (board[y][x]->getRep() <= "Z")) &&
					 (("a" <= board[newy][newx]->getRep()) &&
					  (board[newy][newx]->getRep() <= "z")))
			{

				delete board[newy][newx]; // we can make it track the number of pieces left by making the destructor body decrement a field. (I didn't implement yet)

				board[newy][newx] = board[y][x];
				board[y][x] = nullptr;
				board[newy][newx]->setPos(newy, newx);
			}

			updateBoardMoves();
		}
		else if (result == 1)
		{

			board[newy][newx] = board[y][x];
			board[y][x] = nullptr;
			board[newy][newx]->setPos(newy, newx);

			updateBoardMoves();
		}
		else if (result == 0)
		{

			// do nothing
		}
	}
}

// updates the move possiblities for the pieces on the board
// should be called after each move
void twoPlayerBoard::updateBoardMoves()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{

			board[i][j]->updateMoves();
		}
	}
}

void twoPlayerBoard::origSetup()
{

	board[0][0] = new Rook{false};
	board[0][0]->setPos(0, 0);
	board[0][0]->attach(this);
	board[0][1] = new Knight{false};
	board[0][1]->setPos(0, 1);
	board[0][1]->attach(this);
	board[0][2] = new Bishop{false};
	board[0][2]->setPos(0, 2);
	board[0][2]->attach(this);
	board[0][3] = new Queen{false};
	board[0][3]->setPos(0, 3);
	board[0][3]->attach(this);
	board[0][4] = new King{false};
	board[0][4]->setPos(0, 4);
	board[0][4]->attach(this);
	board[0][5] = new Bishop{false};
	board[0][5]->setPos(0, 5);
	board[0][5]->attach(this);
	board[0][6] = new Knight{false};
	board[0][6]->setPos(0, 6);
	board[0][6]->attach(this);
	board[0][7] = new Rook{false};
	board[0][7]->setPos(0, 7);
	board[0][7]->attach(this);

	for (int i = 0; i < 8; ++i)
	{
		board[1][i] = new Pawn{false};
		board[1][i]->setPos(1, i);
		board[1][i]->attach(this);
	}

	board[7][0] = new Rook{true};
	board[7][0]->setPos(7, 0);
	board[7][0]->attach(this);
	board[7][1] = new Knight{true};
	board[7][1]->setPos(7, 1);
	board[7][1]->attach(this);
	board[7][2] = new Bishop{true};
	board[7][2]->setPos(7, 2);
	board[7][2]->attach(this);
	board[7][3] = new Queen{true};
	board[7][3]->setPos(7, 3);
	board[7][3]->attach(this);
	board[7][4] = new King{true};
	board[7][4]->setPos(7, 4);
	board[7][4]->attach(this);
	board[7][5] = new Bishop{true};
	board[7][5]->setPos(7, 5);
	board[7][5]->attach(this);
	board[7][6] = new Knight{true};
	board[7][6]->setPos(7, 6);
	board[7][6]->attach(this);
	board[7][7] = new Rook{true};
	board[7][7]->setPos(7, 7);
	board[7][7]->attach(this);

	for (int i = 0; i < 8; ++i)
	{
		board[6][i] = new Pawn{true};
		board[6][i]->setPos(6, i);
		board[6][i]->attach(this);
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
					cout << ' ';
				}
				else
				{ // otherwise it's a black tile

					cout << '_';
				}
			}
			else
			{ // piece is on it
				board[i][j]->getRep();
			}
		}
		cout << endl;
	}
	cout << endl
		 << "  ";
	for (int i = 0; i < 8; ++i)
	{
		cout << 'a' + i;
	}
	cout << endl;
}

void twoPlayerBoard::insertNewPiece(string validpiece, string position)
{

	if (('0' <= position[1] <= '7') && ('a' <= position[0] <= 'h'))
	{

		if (validpiece == "K")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new King{true};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "k")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new King{false};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "Q")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Queen{true};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "q")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Queen{false};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "R")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Rook{true};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "r")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Rook{false};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "B")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Bishop{true};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "b")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Bishop{false};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "N")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Knight{true};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "n")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Knight{false};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "P")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Pawn{true};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
		else if (validpiece == "p")
		{

			if (board[8 - (position[1] - '0')][position[0] - 'a'])
			{
				delete board[8 - (position[1] - '0')][position[0] - 'a'];
			}

			board[8 - (position[1] - '0')][position[0] - 'a'] = new Pawn{false};
			board[8 - (position[1] - '0')][position[0] - 'a']->setPos(8 - (position[1] - '0'), position[0] - 'a');
		}
	}
}

void twoPlayerBoard::removePiece(string position)
{
	if (board[8 - (position[1] - '0')][position[0] - 'a'])
	{
		delete board[8 - (position[1] - '0')][position[0] - 'a'];
	}
}

bool twoPlayerBoard::kingInCheck(bool isWhite)
{ // not checkmate
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{

			if (board[i][j]->kingCheck())
			{				 // if at least one piece has check (isWhite tells us if black king is in check)
				return true; // then the king is in check
			}
		}
	}
	// otherwise they all not have check so
	return false;
}

bool twoPlayerBoard::verifySetup()
{ // uses the character matrix
	int numWhiteKings = 0;
	int numBlackKings = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			// check one white and black king

			if (board[i][j]->getRep() == "k")
			{
				++numBlackKings;
			}
			else if (board[i][j]->getRep() == "K")
			{
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

			// check if neither king is in check

			if (kingInCheck(true) || kingInCheck(false))
			{				  // if either king is in check (white or black)
				return false; // return false
			}
		}
	}

	if (numWhiteKings != 1 || numBlackKings != 1)
	{

		return false;
	}
	else
	{ // if all conditions are satisfied return true

		return true;
	}
}