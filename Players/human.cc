#include "human.h"
#include "../PiecesAndBoard/board.h"
using namespace std;

Human::Human(int side) : Player{side, 0} {}

// hello

/*
# return 0 if ask for different move (move failed)
# return 1 if move was successful (ask for next move) (NORMAL MOVE)
# return 2 if capture was sucessful (ask for next move) (CAPTURE MOVE)
# return 3 if move was CASTLE
# return 4 if move was ENPASSANT
# return 5 if move was PROMOTION


THE STRING FIELD CONTAINS RELEVANT INFORMATION ABOUT THOSE MOVES (FOR MOVE OBJECT)
*/

std::pair<int, std::string> Human::playerMove(int oldCol, int oldRow, int newCol, int newRow)
{
    Piece *pieceToMove = gameBoard->getPiece(oldCol, oldRow);
    if (pieceToMove)
    {
        if (pieceToMove->getSide() != side || pieceToMove->move(newCol, newRow) == 0)
        {
            return pair<int, std::string>{0, "fail"};
        }
        else if (pieceToMove->move(newCol, newRow) == 1)
        {
            gameBoard->moveP(oldCol, oldRow, newCol, newRow);
            return pair<int, std::string>{1, "normal"};
        }
        else if (pieceToMove->move(newCol, newRow) == 2)
        {

            std::string capturedRep = gameBoard->getPiece(newCol, newRow)->getRep();
            opponent->removePiece(std::pair<int, int>{newCol, newRow});
            gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow);
            return pair<int, std::string>{2, capturedRep};
        }
        else if (pieceToMove->move(newCol, newRow) == 3)
        { // CASTLE CONDITION

            return pair<int, std::string>{3, "castle"};
        }
        else if (pieceToMove->move(newCol, newRow) == 4)
        { // ENPASSANT CONDITION

            return pair<int, std::string>{4, "enpassant"};
        }
        else if (pieceToMove->move(newCol, newRow) == 5)
        { // PROMOTION CONDITION

            return pair<int, std::string>{5, "promotion"};
        }
    }
    return pair<int, std::string>{0, "fail"};
}