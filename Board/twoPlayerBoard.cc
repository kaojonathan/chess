#include <iostream>
#include <string>
#include <memory>
#include "../Pieces/piece.h"
#include "twoPlayerBoard.h"
#include "board.h"
#include "../Pieces/rook.h"
#include "../Pieces/bishop.h"
#include "../Pieces/king.h"
#include "../Pieces/queen.h"
#include "../Pieces/knight.h"
#include "../Pieces/pawn.h"
using namespace std;

twoPlayerBoard::twoPlayerBoard() : Board{} {} // constructor, initializes a board

shared_ptr<Piece> twoPlayerBoard::shareP(int x, int y)
{ // returns a shared pointer of the piece at pos (x, y)
	return board[y][x];
}

Piece* twoPlayerBoard::getP(int x, int y) 
{ // returns a raw pointer of the piece at pos (x, y)
	return board[y][x].get();
}

bool twoPlayerBoard::validPos(int x, int y)
{ // returns true of the (x, y) position is in the board
	return 0 <= x && 0 <= y && x < 8 && y < 8;
}

void twoPlayerBoard::movePiece(int x, int y, int newx, int newy)
{ // moves a piece at position (x, y) to (newx, newy)
	board[y][x]->incNumMoves(); // increase the number of moves of that piece
	// change positions
	board[y][x]->setPos(newx, newy);
	board[newy][newx] = board[y][x];
	board[y][x] = nullptr;
}

void twoPlayerBoard::castle(int col, int row)
{
	if (col == 6 && row == 7)
	{ // bottom right castle
		// increase the number of moves of king
		board[7][4]->incNumMoves();
		// change positions of the king
		board[7][4]->setPos(6, 7);
		board[7][6] = board[7][4];
		board[7][4] = nullptr;

		// increase the number of moves of rook
		board[7][7]->incNumMoves();
		// change positions of the rook
		board[7][7]->setPos(5, 7);
		board[7][5] = board[7][7];
		board[7][7] = nullptr;
	}
	else if (col == 2 && row == 7)
	{ // bottom left castle
		// increase the number of moves of king
		board[7][4]->incNumMoves();
		// change positions of the king
		board[7][4]->setPos(2, 7);
		board[7][2] = board[7][4];
		board[7][4] = nullptr;

		// increase the number of moves of rook
		board[7][0]->incNumMoves();
		// change positions of the rook
		board[7][0]->setPos(3, 7);
		board[7][3] = board[7][0];
		board[7][0] = nullptr;
	}
	else if (col == 6 && row == 0)
	{ // top right castle
		// increase the number of moves of king
		board[0][4]->incNumMoves();
		// change positions of the king
		board[0][4]->setPos(6, 0);
		board[0][6] = board[0][4];
		board[0][4] = nullptr;

		// increase the number of moves of rook
		board[0][7]->incNumMoves();
		// change positions of the rook
		board[0][7]->setPos(5, 0);
		board[0][5] = board[0][7];
		board[0][7] = nullptr;
	}
	else if (col == 2 && row == 0)
	{ // top left castle
		// increase the number of moves of king
		board[0][4]->incNumMoves();
		// change positions of the king
		board[0][4]->setPos(2, 0);
		board[0][2] = board[0][4];
		board[0][4] = nullptr;

		// increase the number of moves of rook
		board[0][0]->incNumMoves();
		// change positions of the rook
		board[0][0]->setPos(3, 0);
		board[0][3] = board[0][0];
		board[0][0] = nullptr;
	}
}

void twoPlayerBoard::capturePiece(int newx, int newy)
{ // captures the piece at pos (x, y)
	board[newy][newx] = nullptr;
}

void twoPlayerBoard::insertNewPiece(string name, string position)
{ // inserts a new valid piece at position
	int row = 8 - (position[1] - '0');
	int col = position[0] - 'a';
	if (board[row][col])
	{ // if there is already a piece set it null first
		board[row][col] = nullptr;
	}
	// insert the corresponding piece by making a new piece at that position
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
{ // removes a piece at position
	int row = 8 - (position[1] - '0');
	int col = position[0] - 'a';
	if (board[row][col])
	{ // if there is a piece at that position set it null
		board[row][col] = nullptr;
	}
}

bool twoPlayerBoard::verifySetup()
{ // verifies if the setup of the chess pieces is valid according to the assignment guidelines
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
				if (board[i][j]->getRep() == "k")
				{
					blackKing = board[i][j].get();
					++numBlackKings; // increment the number of black kings on the board
				}
				else if (board[i][j]->getRep() == "K")
				{
					whiteKing = board[i][j].get();
					++numWhiteKings; // increment the number of white kings on the board
				}
				// check if there are no pawns on the first or last row of board
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
	{ // check if there is one white and one black king ONLY
		return false;
	}
	else
	{ // if these conditions are satisfied, check if neither king is in check
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (board[i][j])
				{ // if a piece is at pos (i, j) on the board, get its attackable pieces.
					std::vector<Piece *> attackablePieces = board[i][j]->getAttackable(std::pair<int, int>{board[i][j]->getX(), board[i][j]->getY()});
					for (int i = 0; i < attackablePieces.size(); ++i)
					{ // iterate over them
					// if one of them is white king or black king, return false.
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
		// after this loop everything is satisfied.
		return true;
	}
}

void twoPlayerBoard::origSetup()
{ // sets up the board with pieces like an original chess game
// insert the pieces in their correct positions on the board (original)
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
