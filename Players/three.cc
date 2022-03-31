#include "three.h"
#include "../PiecesAndBoard/board.h"
#include <utility>
using namespace std;

Three::Three(int side, int level) : Computer{side, level} {}

void Three::move()
{

	// AVOIDING MOVES CONDITION (this needs implement)

	for (int i = 0; i < pieces.size(); ++i)
	{
		for (int j = 0; j < opponent->getPieces().size(); ++j)
		{

			if (opponent->getPieces()[j]->canAttack(std::pair<int, int>{pieces[i]->getX(), pieces[i]->getY()}))
			{ // if an enemy piece is about to capture it

				for (int k = 0; k < pieces[i]->getMoves().size(); ++k)
				{

					if (!opponent->getPieces()[j]->canAttack(pieces[i]->getMoves()[k]))
					{ // if the same enemy piece can't attack a current piece's move position

						if (pieces[i]->move(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second) == 2)
						{
							opponent->removePiece(std::pair<int, int>{pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second});
						}

						gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second); // move to that position

						return;
					}
				}
			}
		}
	}

	// CAPTURE CONDITION
	for (int i = 0; i < pieces.size(); ++i)
	{

		for (int j = 0; j < 8; ++j)
		{

			for (int k = 0; k < 8; ++k)
			{
				if (pieces[i]->move(j, k) == 2)
				{ // if the move is capture then move it
					opponent->removePiece(std::pair<int, int>{j, k});
					gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);
					return;
				}
			}
		}
	}

	// CHECK CONDITION
	for (int i = 0; i < pieces.size(); ++i)
	{

		for (int j = 0; j < 8; ++j)
		{

			for (int k = 0; k < 8; ++k)
			{

				if (pieces[i]->posInCheck(j, k))
				{ // finds position of the piece that checks the king

					if (pieces[i]->move(j, k) != 0)
					{ // if the move is valid then move it
						if (pieces[i]->move(j, k) == 2)
						{
							opponent->removePiece(std::pair<int, int>{j, k});
						}

						gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);
						return;
					}
				}
			}
		}
	}

	// otherwise random legal move
	bool madeMove = false;
	while (!madeMove)
	{											 // keep looping if we haven't made a move
		int pieceIndex = rand() % pieces.size(); // randomly give us an x-coordinate
		int i = rand() % 8;						 // randomly give us an x-coordinate
		int j = rand() % 8;						 // randomly give us a y-coordinate
		if (pieces[pieceIndex]->move(i, j) != 0)
		{ // if the move is valid then move it
			if (pieces[pieceIndex]->move(i, j) == 2)
			{
				opponent->removePiece(std::pair<int, int>{i, j});
			}

			gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
			madeMove = true;
		}
		// otherwise keep looping (might be inefficient)
	}
}