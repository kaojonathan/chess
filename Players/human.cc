#include "human.h"
#include "../PiecesAndBoard/board.h"
using namespace std;

Human::Human(int side) : Player{side, 0} {}

// hello
/*
# return 0 if ask for different move (move failed)
# return 1 if move was successful (ask for next move)
# return 2 if capture was sucessful (ask for next move)
*/
int Human::playerMove(int oldCol, int oldRow, int newCol, int newRow)
{
    Piece *pieceToMove;
    pieceToMove = gameBoard->getPiece(oldCol, oldRow);
    if (pieceToMove)
    {
        if (pieceToMove->move(newCol, newRow) == 0)
        {
            return 0;
        }
        else if (pieceToMove->move(newCol, newRow) == 1)
        {
            gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow);
            return 1;
        }
        else if (pieceToMove->move(newCol, newRow) == 2)
        {
            opponent->removePiece(std::pair<int, int>{pieceToMove->getX(), pieceToMove->getY()});
            gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow);
            return 2;
        }
    } 
    else
        return 0;
}