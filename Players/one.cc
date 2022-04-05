#include "one.h"
#include "../Board/board.h"
#include <iostream>
using namespace std;

// constructor
One::One(int side, int level) : Computer{side, level} {}

// moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
// returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
std::pair<int, std::string> One::move(int &oldCol, int &oldRow, int &newCol, int &newRow)
{
	int moveKing = rand() % pieces.size(); // randomize 
	if (moveKing == 0)
	{ // if 0 is chosen choose king
		while (1)
		{						// keep looping if we haven't made a move
			int i = rand() % 8; // randomly give us an x-coordinate
			int j = rand() % 8; // randomly give us a y-coordinate
			if (king->move(i, j) != 0)
			{ // if the move is valid then move it
				if (king->move(i, j) == 1)
				{ // if it's move returns 1 (normal)
					oldCol = king->getX(); // update the parameters with the move positions
					oldRow = king->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(king->getX(), king->getY(), i, j); // move the piece on the board; return pair with (1, "normal")
					return pair<int, std::string>{1, "normal"};
				} 
				else if (king->move(i, j) == 2)
				{ // if it's move returns 2 (capture)
					std::string capturedRep = gameBoard->getPiece(i, j)->getRep(); // get the captured type
					opponent->removePiece(std::pair<int, int>{i, j}); // remove the piece from opponent
					oldCol = king->getX(); // update the parameters with the move positions
					oldRow = king->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(king->getX(), king->getY(), i, j); // move the piece on the board; return pair with (2, capturedRep)
					return pair<int, std::string>{2, capturedRep};
				}
				else if (king->move(i, j) == 3)
				{ // if it's move returns 3 (castle)
					oldCol = king->getX(); // update the parameters with the move positions
					oldRow = king->getY();
					newCol = i;
					newRow = j;
					gameBoard->doCastle(newCol, newRow); // do castle on game board; return pair with (3, "castle")
					return pair<int, std::string>{3, "castle"};
				}
				else if (king->move(i, j) == 4)
				{ // if it's move returns 4 (promotion)
					oldCol = king->getX(); // update the parameters with the move positions
					oldRow = king->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(king->getX(), king->getY(), i, j); // move the piece on the board
					deletePiece(std::pair<int, int>(i, j)); // delete piece from player; return pair with (4, "promotion")
					return pair<int, std::string>{4, "promotion"};
				}
				else if (king->move(i, j) == 5)
				{ // if it's move returns 5 (promotion with capture)
					std::string capturedRep = gameBoard->getPiece(i, j)->getRep(); // get the captured type
					opponent->removePiece(std::pair<int, int>{i, j}); // remove the piece from opponent
					oldCol = king->getX(); // update the parameters with the move positions
					oldRow = king->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(king->getX(), king->getY(), i, j); // move the piece on the board
					deletePiece(std::pair<int, int>(i, j)); // delete piece from player; return pair with (5, capturedRep)
					return pair<int, std::string>{5, capturedRep};
				}
			}
			// otherwise keep looping
		}
	}
	else
	{ // if 0 is not chosen
		while (1)
		{											 // keep looping if we haven't made a move
			int pieceIndex = rand() % pieces.size(); // randomly give us a piece
			int i = rand() % 8;						 // randomly give us an x-coordinate
			int j = rand() % 8;						 // randomly give us a y-coordinate
			if (pieces[pieceIndex]->move(i, j) != 0)
			{ // if the move is valid then move it
				if (pieces[pieceIndex]->move(i, j) == 1)
				{ // if it's move returns 1 (normal)
					oldCol = pieces[pieceIndex]->getX(); // update the parameters with the move positions
					oldRow = pieces[pieceIndex]->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j); // move the piece on the board; return pair with (1, "normal")
					return pair<int, std::string>{1, "normal"};
				}
				else if (pieces[pieceIndex]->move(i, j) == 2)
				{ // if it's move returns 2 (capture)
					std::string capturedRep = gameBoard->getPiece(i, j)->getRep(); // get the captured type
					opponent->removePiece(std::pair<int, int>{i, j});
					oldCol = pieces[pieceIndex]->getX(); // update the parameters with the move positions
					oldRow = pieces[pieceIndex]->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j); // move the piece on the board; return pair with (2, capturedRep)
					return pair<int, std::string>{2, capturedRep};
				}
				else if (pieces[pieceIndex]->move(i, j) == 3)
				{ // if it's move returns 3 (castle)
					oldCol = pieces[pieceIndex]->getX(); // update the parameters with the move positions
					oldRow = pieces[pieceIndex]->getY();
					newCol = i;
					newRow = j;
					gameBoard->doCastle(newCol, newRow); // do castle on game board; return pair with (3, "castle")
					return pair<int, std::string>{3, "castle"};
				}
				else if (pieces[pieceIndex]->move(i, j) == 4)
				{ // if it's move returns 4 (promotion)
					oldCol = pieces[pieceIndex]->getX(); // update the parameters with the move positions
					oldRow = pieces[pieceIndex]->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j); // move the piece on the board
					deletePiece(std::pair<int, int>(i, j)); // delete piece from player; return pair with (4, "promotion")
					return pair<int, std::string>{4, "promotion"};
				}
				else if (pieces[pieceIndex]->move(i, j) == 5)
				{ // if it's move returns 5 (promotion with capture)
					std::string capturedRep = gameBoard->getPiece(i, j)->getRep(); // get the captured type
					opponent->removePiece(std::pair<int, int>{i, j}); // remove the piece from opponent
					oldCol = pieces[pieceIndex]->getX(); // update the parameters with the move positions
					oldRow = pieces[pieceIndex]->getY();
					newCol = i;
					newRow = j;
					gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j); // move the piece on the board
					deletePiece(std::pair<int, int>(i, j)); // delete piece from player; return pair with (5, capturedRep)
					return pair<int, std::string>{5, capturedRep};
				}
				else if (pieces[pieceIndex]->move(i, j) == 6)
				{ // if it's move returns 6 (enPassant)
					oldCol = pieces[pieceIndex]->getX(); // update the parameters with the move positions
					oldRow = pieces[pieceIndex]->getY();
					newCol = i;
					newRow = j;
					if (pieces[pieceIndex]->getRep() == "P")
					{ // if white pawn
						opponent->removePiece(std::pair<int, int>{i, j + 1}); // remove the piece from opponent
						gameBoard->captureP(i, j + 1); // capture the piece
					}
					else if (pieces[pieceIndex]->getRep() == "p")
					{ // if black pawn
						opponent->removePiece(std::pair<int, int>{i, j - 1}); // remove the piece from opponent
						gameBoard->captureP(i, j - 1); // capture the piece
					}
					gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j); // move the piece on the board; return pair with (6, "enPassant")
					return pair<int, std::string>{6, "enPassant"};
				}
				// otherwise keep looping (might be inefficient)
			}
		}
	}
	return pair<int, std::string>{0, "fail"}; // return (0, "fail")
}