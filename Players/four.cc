#include "four.h"
#include "computer.h"
#include <utility>
#include "../PiecesAndBoard/board.h"
using namespace std;

Four::Four(int side, int level) : Computer{ side, level } {}


// IDK IF WERE DOING FOUR LOLOLOLOL

























































std::pair<int, std::string> Four::move(int &oldCol, int &oldRow, int &newCol, int &newRow)
{
std::cerr << "four  playermove";
/*
	// AVOIDING MOVES CONDITION (this needs implement)

	for (int i = 0; i < pieces.size(); ++i)
	{
		for (int j = 0; j < opponent->getPieces().size(); ++j) {

			if (opponent->getPieces()[j]->canAttack(std::pair<int, int>{pieces[i]->getX(), pieces[i]->getY()})) { // if an enemy piece is about to capture it


			for (int k = 0; k < pieces[i]->getMoves().size(); ++k) {

				if (!opponent->getPieces()[j]->canAttack(pieces[i]->getMoves()[k])) { // if the same enemy piece can't attack a current piece's move position 



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
        int jmax = -1;
        int kmax = -1;
        int currentmax = 0;
		for (int j = 0; j < 8; ++j)
		{
			for (int k = 0; k < 8; ++k)
			{
				if (pieces[i]->move(j, k) == 2)
				{ // if the move is capture
                    if (currentmax < gameBoard->getPiece(j, k)->getVal()) { // find highest value capture!
                        currentmax = gameBoard->getPiece(j, k)->getVal();
                        jmax = j;
                        kmax = k;
                    }
				}
			}
		}

        if (currentmax != 0) {
            gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), jmax, kmax); // capture it!!!
            return;
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

			if (pieces[pieceIndex]->move(i, j) == 1)
			{
				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				return pair<int, std::string>{1, "normal"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 2)
			{

				std::string capturedRep = gameBoard->getPiece(i, j)->getRep();
				opponent->removePiece(std::pair<int, int>{i, j});

				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				return pair<int, std::string>{2, capturedRep};
			}
			else if (pieces[pieceIndex]->move(i, j) == 3)
			{ // CASTLE CONDITION

				return pair<int, std::string>{3, "castle"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 4)
			{ // ENPASSANT CONDITION

				return pair<int, std::string>{4, "enpassant"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 5)
			{ // PROMOTION CONDITION

				return pair<int, std::string>{5, "promotion"};
			}

			madeMove = true;
		}

		// otherwise keep looping (might be inefficient)
	}

*/
	return pair<int, std::string>{0, "fail"};


}