#include "three.h"
#include "../PiecesAndBoard/board.h"
#include <utility>
using namespace std;

Three::Three(int side, int level) : Computer{side, level} {}

std::pair<int, std::string> Three::move(int &oldCol, int &oldRow, int &newCol, int &newRow)
{

std::cerr << "three  playermove";
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


			if (pieces[i]->move(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second) == 1)
			{

				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = pieces[i]->getMoves()[k].first;
				newRow = pieces[i]->getMoves()[k].second;

				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second); // move to that position
				return pair<int, std::string>{1, "normal"};
			}
			else if (pieces[i]->move(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second) == 2)
			{

				std::string capturedRep = gameBoard->getPiece(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second)->getRep();


				opponent->removePiece(std::pair<int, int>{pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second});

				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = pieces[i]->getMoves()[k].first;
				newRow = pieces[i]->getMoves()[k].second;


				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second); // move to that position
				return pair<int, std::string>{2, capturedRep};
			}
			else if (pieces[i]->move(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second) == 3)
			{ // CASTLE CONDITION

				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = pieces[i]->getMoves()[k].first;
				newRow = pieces[i]->getMoves()[k].second;
				return pair<int, std::string>{3, "castle"};
			}
			else if (pieces[i]->move(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second) == 4)
			{ // promo CONDITION
				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = pieces[i]->getMoves()[k].first;
				newRow = pieces[i]->getMoves()[k].second;
				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second);
				
				return pair<int, std::string>{4, "promotion"};
			}
			else if (pieces[i]->move(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second) == 5)
			{ // PROMOTION CONDITION (with cap)
				std::string capturedRep = gameBoard->getPiece(pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second)->getRep();


				opponent->removePiece(std::pair<int, int>{pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second});

				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = pieces[i]->getMoves()[k].first;
				newRow = pieces[i]->getMoves()[k].second;


				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), pieces[i]->getMoves()[k].first, pieces[i]->getMoves()[k].second); // move to that position
				return pair<int, std::string>{5, capturedRep};
			}

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
				std::string capturedRep = gameBoard->getPiece(j, k)->getRep();
					opponent->removePiece(std::pair<int, int>{j, k});

														oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = j;
				newRow = k;


					gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);
					return pair<int, std::string>{2, capturedRep};
				} else if  (pieces[i]->move(j, k) == 5) {


				std::string capturedRep = gameBoard->getPiece(j, k)->getRep();
				opponent->removePiece(std::pair<int, int>{j, k});

				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = j;
				newRow = k;

				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);
				return pair<int, std::string>{5, capturedRep};
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


			if (pieces[i]->move(j, k) == 1)
			{

								oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = j;
				newRow = k;


				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);
				return pair<int, std::string>{1, "normal"};
			}
			else if (pieces[i]->move(j, k) == 2)
			{

				std::string capturedRep = gameBoard->getPiece(j, k)->getRep();
				opponent->removePiece(std::pair<int, int>{j, k});
				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = j;
				newRow = k;
				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);
				return pair<int, std::string>{2, capturedRep};
			}
			else if (pieces[i]->move(j, k) == 3)
			{ // CASTLE CONDITION
				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = j;
				newRow = k;
				return pair<int, std::string>{3, "castle"};
			}
			else if (pieces[i]->move(j, k) == 4)
			{ // promo CONDITION
				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = j;
				newRow = k;

	gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);

				return pair<int, std::string>{4, "promotion"};
			}
			else if (pieces[i]->move(j, k) == 5)
			{ // PROMOTION CONDITION (cap)
				std::string capturedRep = gameBoard->getPiece(j, k)->getRep();
				opponent->removePiece(std::pair<int, int>{j, k});

				oldCol = pieces[i]->getX();
				oldRow = pieces[i]->getY();
				newCol = j;
				newRow = k;

				gameBoard->moveP(pieces[i]->getX(), pieces[i]->getY(), j, k);
				return pair<int, std::string>{5, capturedRep};
			}
				}
			}
		}
	}

	// otherwise random legal move

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
			{ // promo CONDITION
				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;


				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				
				return pair<int, std::string>{4, "promotion"};
			}
			else if (pieces[pieceIndex]->move(i, j) == 5)
			{ // PROMOTION CONDITION (with cap)
				std::string capturedRep = gameBoard->getPiece(i, j)->getRep();
				opponent->removePiece(std::pair<int, int>{i, j});
				oldCol = pieces[pieceIndex]->getX();
				oldRow = pieces[pieceIndex]->getY();
				newCol = i;
				newRow = j;
				gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
				return pair<int, std::string>{5, capturedRep};
			}

		}

		// otherwise keep looping (might be inefficient)
	}

	return pair<int, std::string>{0, "fail"};
}