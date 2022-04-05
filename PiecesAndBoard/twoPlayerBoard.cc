#include <iostream>
#include <string>
#include <memory>
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

twoPlayerBoard::twoPlayerBoard() : Board{} {}

shared_ptr<Piece> twoPlayerBoard::shareP(int x, int y)
{
	return board[y][x];
}

Piece* twoPlayerBoard::getP(int x, int y) 
{
	return board[y][x].get();
}

// returns true of the (x, y) position is in the board
bool twoPlayerBoard::validPos(int x, int y)
{
	return 0 <= x && 0 <= y && x < 8 && y < 8;
}

void twoPlayerBoard::movePiece(int x, int y, int newx, int newy)
{
	board[y][x]->incNumMoves();
	board[y][x]->setPos(newx, newy);
	board[newy][newx] = board[y][x];
	board[y][x] = nullptr;
}

void twoPlayerBoard::castle(int col, int row)
{
	if (col == 6 && row == 7)
	{
		// move king
		board[7][4]->incNumMoves();
		board[7][4]->setPos(6, 7);
		board[7][6] = board[7][4];
		board[7][4] = nullptr;

		// move rook

		board[7][7]->incNumMoves();
		board[7][7]->setPos(5, 7);
		board[7][5] = board[7][7];
		board[7][7] = nullptr;
	}
	else if (col == 2 && row == 7)
	{

		// move king
		board[7][4]->incNumMoves();
		board[7][4]->setPos(2, 7);
		board[7][2] = board[7][4];
		board[7][4] = nullptr;

		// move rook

		board[7][0]->incNumMoves();
		board[7][0]->setPos(3, 7);
		board[7][3] = board[7][0];
		board[7][0] = nullptr;
	}
	else if (col == 6 && row == 0)
	{

		// move king
		board[0][4]->incNumMoves();
		board[0][4]->setPos(6, 0);
		board[0][6] = board[0][4];
		board[0][4] = nullptr;

		// move rook

		board[0][7]->incNumMoves();
		board[0][7]->setPos(5, 0);
		board[0][5] = board[0][7];
		board[0][7] = nullptr;
	}
	else if (col == 2 && row == 0)
	{

		// move king
		board[0][4]->incNumMoves();
		board[0][4]->setPos(2, 0);
		board[0][2] = board[0][4];
		board[0][4] = nullptr;

		// move rook

		board[0][0]->incNumMoves();
		board[0][0]->setPos(3, 0);
		board[0][3] = board[0][0];
		board[0][0] = nullptr;
	}
}

void twoPlayerBoard::capturePiece(int newx, int newy)
{
	board[newy][newx] = nullptr;
}

void twoPlayerBoard::insertNewPiece(string name, string position)
{
	int row = 8 - (position[1] - '0');
	int col = position[0] - 'a';
	if (board[row][col])
	{
		board[row][col] = nullptr;
	}
	if (name == "K")
	{
		board[row][col] = shared_ptr<King> { new King{0, col, row, this}};
	}
	else if (name == "k")
	{
		board[row][col] = shared_ptr<King> { new King{1, col, row, this}};
	}
	else if (name == "Q")
	{
		board[row][col] = shared_ptr<Queen> { new Queen{0, col, row, this}};
	}
	else if (name == "q")
	{
		board[row][col] = shared_ptr<Queen> { new Queen{1, col, row, this}};
	}
	else if (name == "R")
	{
		board[row][col] = shared_ptr<Rook> { new Rook{0, col, row, this}};
	}
	else if (name == "r")
	{
		board[row][col] = shared_ptr<Rook> { new Rook{1, col, row, this}};
	}
	else if (name == "P")
	{
		board[row][col] = shared_ptr<Pawn> { new Pawn{0, col, row, this}};
	}
	else if (name == "p")
	{
		board[row][col] = shared_ptr<Pawn> { new Pawn{1, col, row, this}};
	}
	else if (name == "B")
	{
		board[row][col] = shared_ptr<Bishop> { new Bishop{0, col, row, this}};
	}
	else if (name == "b")
	{
		board[row][col] = shared_ptr<Bishop> { new Bishop{1, col, row, this}};
	}
	else if (name == "N")
	{
		board[row][col] = shared_ptr<Knight> { new Knight{0, col, row, this}};
	}
	else if (name == "n")
	{
		board[row][col] = shared_ptr<Knight> { new Knight{1, col, row, this}};
	}
}

void twoPlayerBoard::removePiece(string position)
{
	int row = 8 - (position[1] - '0');
	int col = position[0] - 'a';
	if (board[row][col])
	{
		board[row][col] = nullptr;
	}
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
					blackKing = board[i][j].get();
					++numBlackKings;
				}
				else if (board[i][j]->getRep() == "K")
				{
					whiteKing = board[i][j].get();
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

					std::vector<Piece *> attackablePieces = board[i][j]->getAttackable(std::pair<int, int>{board[i][j]->getX(), board[i][j]->getY()});

					for (int i = 0; i < attackablePieces.size(); ++i)
					{
						if (attackablePieces[i] == whiteKing)
						{
							return false;
						}
						else if (attackablePieces[i] == blackKing)
						{

							return false;
						}
					}
				}
			}
		}
		return true;
	}
}

void twoPlayerBoard::origSetup()
{

	board[0][0] = shared_ptr<Rook> { new Rook{1, 0, 0, this}};
	board[0][1] = shared_ptr<Knight> { new Knight{1, 1, 0, this}};
	board[0][2] = shared_ptr<Bishop> { new Bishop{1, 2, 0, this}};
	board[0][3] = shared_ptr<Queen> { new Queen{1, 3, 0, this}};
	board[0][4] = shared_ptr<King> { new King{1, 4, 0, this}};
	board[0][5] = shared_ptr<Bishop> { new Bishop{1, 5, 0, this}};
	board[0][6] = shared_ptr<Knight> { new Knight{1, 6, 0, this}};
	board[0][7] = shared_ptr<Rook> { new Rook{1, 7, 0, this}};

	for (int i = 0; i < 8; ++i)
	{
		board[1][i] = shared_ptr<Pawn> { new Pawn{1, i, 1, this}};
	}

	board[7][0] = shared_ptr<Rook> { new Rook{0, 0, 7, this}};
	board[7][1] = shared_ptr<Knight> { new Knight{0, 1, 7, this}};
	board[7][2] = shared_ptr<Bishop> { new Bishop{0, 2, 7, this}};
	board[7][3] = shared_ptr<Queen> { new Queen{0, 3, 7, this}};
	board[7][4] = shared_ptr<King> { new King{0, 4, 7, this}};
	board[7][5] = shared_ptr<Bishop> { new Bishop{0, 5, 7, this}};
	board[7][6] = shared_ptr<Knight> { new Knight{0, 6, 7, this}};
	board[7][7] = shared_ptr<Rook> { new Rook{0, 7, 7, this}};

	for (int i = 0; i < 8; ++i)
	{
		board[6][i] = shared_ptr<Pawn> { new Pawn{0, i, 6, this}};
	}
}
