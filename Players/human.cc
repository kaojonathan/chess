#include "human.h"
#include "../PiecesAndBoard/board.h"
#include <iostream>
using namespace std;

Human::Human(int side) : Player{side, 0} {}

// hello

/*
# return 0 if ask for different move (move failed)
# return 1 if move was successful (ask for next move) (NORMAL MOVE)
# return 2 if capture was sucessful (ask for next move) (CAPTURE MOVE)
# return 3 if move was CASTLE
# return 4 if move was PROMOTION (no capture)
# 5 if promotion and capture

THE STRING FIELD CONTAINS RELEVANT INFORMATION ABOUT THOSE MOVES (FOR MOVE OBJECT)
*/

std::pair<int, std::string> Human::playerMove(int &oldCol, int &oldRow, int &newCol, int &newRow)
{
std::cerr << "one::move called";
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

        gameBoard->doCastle(newCol, newRow);
            return pair<int, std::string>{3, "castle"};
            
        }
        else if (pieceToMove->move(newCol, newRow) == 4)
        { // promo CONDITION


            
        gameBoard->moveP(oldCol, oldRow, newCol, newRow);
        deletePiece(std::pair<int, int>(newCol, newRow));
             return pair<int, std::string>{4, "promotion"};
        }
        else if (pieceToMove->move(newCol, newRow) == 5)
        { // promo CONDITION with capture

            std::string capturedRep = gameBoard->getPiece(newCol, newRow)->getRep();
            opponent->removePiece(std::pair<int, int>{newCol, newRow});
            gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow);

            deletePiece(std::pair<int, int>(newCol, newRow));

             return pair<int, std::string>{5, capturedRep};
        } else if (pieceToMove->move(newCol, newRow) == 6) {
            // en passant

           
    

		if (pieceToMove->getRep() == "P")
		{
opponent->removePiece(std::pair<int, int>{newCol, newRow + 1});
gameBoard->captureP(newCol, newRow + 1);
		}
		else if (pieceToMove->getRep() == "p")
		{
opponent->removePiece(std::pair<int, int>{newCol, newRow - 1});
gameBoard->captureP(newCol, newRow - 1);
		}

gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow);

             return pair<int, std::string>{6, "enPassant"};

        }
    }
    return pair<int, std::string>{0, "fail"};
}