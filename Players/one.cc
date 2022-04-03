#include "one.h"
#include "../PiecesAndBoard/board.h"
#include <iostream>
using namespace std;

One::One(int side, int level) : Computer{side, level} {}

std::pair<int, std::string> One::move(int &oldCol, int &oldRow, int &newCol, int &newRow)
{
std::cerr << "one playermove";

	int moveKing = rand() % pieces.size();

	if (moveKing == 0) {

	while (1)
	{											 // keep looping if we haven't made a move
		int i = rand() % 8;						 // randomly give us an x-coordinate
		int j = rand() % 8;						 // randomly give us a y-coordinate




		if (king->move(i, j) != 0)
		{ // if the move is valid then move it

			if (king->move(i, j) == 1)
			{
				oldCol = king->getX();
				oldRow = king->getY();
				newCol = i;
				newRow = j;
				gameBoard->moveP(king->getX(), king->getY(), i, j);
				return pair<int, std::string>{1, "normal"};
			}
			else if (king->move(i, j) == 2)
			{

				std::string capturedRep = gameBoard->getPiece(i, j)->getRep();
				opponent->removePiece(std::pair<int, int>{i, j});
				oldCol = king->getX();
				oldRow = king->getY();
				newCol = i;
				newRow = j;
				gameBoard->moveP(king->getX(), king->getY(), i, j);
				return pair<int, std::string>{2, capturedRep};
			}
			else if (king->move(i, j) == 3)
			{ // CASTLE CONDITION



				oldCol = king->getX();
				oldRow = king->getY();
				newCol = i;
				newRow = j;


				


				// gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j); ???


				return pair<int, std::string>{3, "castle"};
			}
			else if (king->move(i, j) == 4)
			{ // Promo CONDITION (no cap)


				oldCol = king->getX();
				oldRow = king->getY();
				newCol = i;
				newRow = j;


				gameBoard->moveP(king->getX(), king->getY(), i, j);
				deletePiece(std::pair<int, int>(i, j));
				
				return pair<int, std::string>{4, "promotion"};
			} else if (king->move(i, j) == 5) {
				// Promo CONDITION (with cap)


				std::string capturedRep = gameBoard->getPiece(i, j)->getRep();
				opponent->removePiece(std::pair<int, int>{i, j});
				oldCol = king->getX();
				oldRow = king->getY();
				newCol = i;
				newRow = j;
				gameBoard->moveP(king->getX(), king->getY(), i, j);
				deletePiece(std::pair<int, int>(i, j));
				return pair<int, std::string>{5, capturedRep};

			} 
		}
		// otherwise keep looping (might be inefficient)
	}

	


	} else {


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


				


				// gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j); ???


				return pair<int, std::string>{3, "castle"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 4)
			{ // Promo CONDITION (no cap)


				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;


				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				deletePiece(std::pair<int, int>(i, j));
				
				return pair<int, std::string>{4, "promotion"};
			} else if (pieces[pieceIndex]->move(i, j) == 5) {
				// Promo CONDITION (with cap)


				std::string capturedRep = gameBoard->getPiece(i, j)->getRep();
				opponent->removePiece(std::pair<int, int>{i, j});
				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;
				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				deletePiece(std::pair<int, int>(i, j));
				return pair<int, std::string>{5, capturedRep};

			} else if (pieces[pieceIndex]->move(i, j) == 6) {
            // en passant

        
				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;

		if (pieces[pieceIndex]->getRep() == "P")
		{
opponent->removePiece(std::pair<int, int>{i, j + 1});
gameBoard->captureP(i, j + 1);
		}
		else if (pieces[pieceIndex]->getRep() == "p")
		{
opponent->removePiece(std::pair<int, int>{i, j - 1});
gameBoard->captureP(i, j - 1);
		}

gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);

             return pair<int, std::string>{6, "enPassant"};
		}
		// otherwise keep looping (might be inefficient)
	}


	}
	}
	return pair<int, std::string>{0, "fail"};
}