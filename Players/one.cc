#include "one.h"
#include "../PiecesAndBoard/board.h"
#include <iostream>
using namespace std;

One::One(int side, int level) : Computer{side, level} {}

std::pair<int, std::string> One::move(int &oldCol, int &oldRow, int &newCol, int &newRow)
{

std::cerr << "one playermove";

	bool madeMove = false;
	while (1)
	{											 // keep looping if we haven't made a move
		int pieceIndex = rand() % pieces.size(); // randomly give us an x-coordinate
		int i = rand() % 8;						 // randomly give us an x-coordinate
		int j = rand() % 8;						 // randomly give us a y-coordinate
		if (pieces[pieceIndex]->move(i, j) != 0)
		{ // if the move is valid then move it

			if (pieces[pieceIndex]->move(i, j) == 1)
			{
				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;
				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				return pair<int, std::string>{1, "normal"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 2)
			{

				std::string capturedRep = gameBoard->getPiece(i, j)->getRep();
				opponent->removePiece(std::pair<int, int>{i, j});
				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;
				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				return pair<int, std::string>{2, capturedRep};
			}
			else if (pieces[pieceIndex]->move(i, j) == 3)
			{ // CASTLE CONDITION



				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;

				return pair<int, std::string>{3, "castle"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 4)
			{ // ENPASSANT CONDITION


				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;


				return pair<int, std::string>{4, "enpassant"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 5)
			{ // PROMOTION CONDITION



				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;


				
				return pair<int, std::string>{5, "promotion"};
			}

			madeMove = true;
		}

		// otherwise keep looping (might be inefficient)
	}

	return pair<int, std::string>{0, "fail"};
}