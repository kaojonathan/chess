#include "human.h"
#include "../Board/board.h"
#include <iostream>
using namespace std;

// constructor
Human::Human(int side) : Player{side, 0} {}

// moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
// returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
std::pair<int, std::string> Human::playerMove(int &oldCol, int &oldRow, int &newCol, int &newRow)
{
    Piece *pieceToMove = gameBoard->getPiece(oldCol, oldRow); // get the piece to move
    if (pieceToMove)
    { // if there is a piece there
        if (pieceToMove->getSide() != side || pieceToMove->move(newCol, newRow) == 0)
        { // if the piece is wrong side or it's move returns 0, return pair with (0, "fail")
            return pair<int, std::string>{0, "fail"};
        }
        else if (pieceToMove->move(newCol, newRow) == 1)
        {                                                     // if it's move returns 1 (normal)
            gameBoard->moveP(oldCol, oldRow, newCol, newRow); // move the piece on the board; return pair with (1, "normal")
            return pair<int, std::string>{1, "normal"};
        }
        else if (pieceToMove->move(newCol, newRow) == 2)
        {                                                                               // if it's move returns 2 (capture)
            std::string capturedRep = gameBoard->getPiece(newCol, newRow)->getRep();    // get the captured type
            opponent->removePiece(std::pair<int, int>{newCol, newRow});                 // remove the piece from opponent
            gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow); // move the piece on the board; return pair with (2, capturedRep)
            return pair<int, std::string>{2, capturedRep};
        }
        else if (pieceToMove->move(newCol, newRow) == 3)
        {                                        // if it's move returns 3 (castle)
            gameBoard->doCastle(newCol, newRow); // do castle on game board; return pair with (3, "castle")
            return pair<int, std::string>{3, "castle"};
        }
        else if (pieceToMove->move(newCol, newRow) == 4)
        {                                                     // if it's move returns 4 (promotion)
            gameBoard->moveP(oldCol, oldRow, newCol, newRow); // move the piece on the board
            deletePiece(std::pair<int, int>(newCol, newRow)); // delete piece from player; return pair with (4, "promotion")
            return pair<int, std::string>{4, "promotion"};
        }
        else if (pieceToMove->move(newCol, newRow) == 5)
        {                                                                               // if it's move returns 5 (promotion with capture)
            std::string capturedRep = gameBoard->getPiece(newCol, newRow)->getRep();    // get the captured type
            opponent->removePiece(std::pair<int, int>{newCol, newRow});                 // remove the piece from opponent
            gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow); // move the piece on the board
            deletePiece(std::pair<int, int>(newCol, newRow));                           // delete piece from player; return pair with (5, capturedRep)
            return pair<int, std::string>{5, capturedRep};
        }
        else if (pieceToMove->move(newCol, newRow) == 6)
        { // if it's move returns 6 (enpassant)
            if (pieceToMove->getRep() == "P")
            {                                                                   // if white pawn
                opponent->removePiece(std::pair<int, int>{newCol, newRow + 1}); // remove the piece from opponent
                gameBoard->captureP(newCol, newRow + 1);                        // capture the piece
            }
            else if (pieceToMove->getRep() == "p")
            {                                                                   // if black pawn
                opponent->removePiece(std::pair<int, int>{newCol, newRow - 1}); // remove the piece from opponent
                gameBoard->captureP(newCol, newRow - 1);                        // capture the piece
            }
            gameBoard->moveP(pieceToMove->getX(), pieceToMove->getY(), newCol, newRow); // move the piece on the board; return pair with (6, "enPassant")
            return pair<int, std::string>{6, "enPassant"};
        }
    }
    return pair<int, std::string>{0, "fail"}; // return (0, "fail")
}