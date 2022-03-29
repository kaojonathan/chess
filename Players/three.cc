#include "three.h"
#include <utility>
using namespace std;

Three::Three(int side, int level) : Computer{ side, level} {}


void Three::move()
{


	// AVOIDING MOVES CONDITION (this needs implement)

	for (int i = 0; i < pieces.size(); ++i)
	{
		for (int j = 0; j < enemypieces.size(); ++j) {

			if (enemypieces[j]->canAttack(std::pair{pieces[i]->getX(), pieces[i]->getY()})) { // if an enemy piece is about to capture it


			// batchest!!!







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
			gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
			madeMove == true;
		}
		// otherwise keep looping (might be inefficient)
	}
}