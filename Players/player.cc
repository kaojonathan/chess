#include "player.h"
#include "../Board/board.h"
#include "../Pieces/piece.h"
#include "../Pieces/rook.h"
#include "../Pieces/bishop.h"
#include "../Pieces/king.h"
#include "../Pieces/queen.h"
#include "../Pieces/knight.h"
#include "../Pieces/pawn.h"
#include <utility>
#include <iostream>
#include <memory>
using namespace std;

// constructor
Player::Player(int side, int type) : side{side}, type{type} {}

// initialize player fields once setup is complete
void Player::init(Board *board, Player *player)
{
    gameBoard = board;
    opponent = player;
}

// get Piece for each players, only use after setup
void Player::claimPieces()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            auto pc = gameBoard->sharePiece(i, j);
            if (pc)
            {
                if (side == pc->getSide())
                {                              // iterate over the board and check if the piece is white/black
                    pc->setOpponent(opponent); // if it matches the type of player emplace it into pieces or king
                    if (pc->isKing())
                        king = pc;
                    else
                        pieces.emplace_back(pc);
                }
            }
        }
    }
}

// destructor
Player::~Player() {}

// set opponentCheck to the Piece
void Player::kingCheckedBy(Piece *enemy)
{
    opponentCheck = enemy;
    for (auto &&piece : pieces)
        piece->forcedBy(enemy, true); // for Pieces that is not king, set the forced field into the given pieces, for King, update the excape route of the king
}

void Player::removePiece(std::pair<int, int> pos)
{ // removes the piece in position (x, y) and places it in inactivePieces.
    for (size_t i = 0; i < pieces.size(); ++i)
    {
        if ((pieces[i]->getX() == pos.first) && (pieces[i]->getY() == pos.second))
        {                                           // find the piece in pieces
            inactivePieces.emplace_back(pieces[i]); // emplace it in inactivePieces
            auto it = pieces.begin() + i;
            it = pieces.erase(it); // remove it from pieces
        }
    }
}

void Player::deletePiece(std::pair<int, int> pos)
{ // deletes the piece in position (x, y)
    for (size_t i = 0; i < pieces.size(); ++i)
    {
        if ((pieces[i]->getX() == pos.first) && (pieces[i]->getY() == pos.second))
        { // find the piece in pieces
            auto it = pieces.begin() + i;
            it = pieces.erase(it); // remove it from pieces
        }
    }
}

// update status of all pieces of the player, return 0 if there is avaliable move for player, 1 if it is a checkmate, 2 if it is a draw.
int Player::checkStatus()
{
    for (auto &&piece : opponent->getPieces())
        piece->statusUpdate(); // update the status of the opponent's pieces
    for (auto &&piece : pieces)
        piece->statusUpdate(); // update the status of this's pieces
    king->statusUpdate();      // update king status
    if (canMove())             // if the player can move
        return 0;
    if (opponentCheck) // if the opponent is in check
        return 1;      // checkmate
    return 2;
}

// unset that status fields of each piece
void Player::unsetStatus()
{
    for (auto &&piece : pieces)
        piece->needsUpdate(); // call needsUpdate on each piece in player
    king->needsUpdate();      // and its king
}

// find all piece of Player can attack position pos
vector<Piece *> Player::canAttack(pair<int, int> pos)
{
    vector<Piece *> res{};
    if (king->isUpdated() && king->canAttack(pos)) // if king is updated and can attack
        res.emplace_back(king.get()); // emplace it into res
    for (auto &&piece : pieces)
    {
        if (piece->canAttack(pos))  // if a piece is updated and can attack
            res.emplace_back(piece.get()); // emplace it into res
    }
    return res; // return res
}

// true if there is any pieces that the player can move
bool Player::canMove()
{
    for (auto &&piece : pieces)
    {
        if ((piece->getMoves().size() != 0) || (piece->getTargets().size() != 0)) // if any of piece or king can move
            return true;
    }
    if ((king->getMoves().size() != 0) || (king->getTargets().size() != 0))
        return true;
    return false;
}

// print players fields DEBUG
void Player::print()
{
    cout << king->getRep() << " at position (" << king->getX() << "," << king->getY() << endl;
    for (auto &&piece : pieces)
    {
        if (!piece)
            cout << "something is wrong in Player::claimPieces()" << endl;
        else
            cout << piece->getRep() << " at position (" << piece->getX() << "," << piece->getY() << ")" << endl;
    }
}

// adds a piece to the player's pieces
void Player::addToPieces(std::shared_ptr<Piece> p)
{
    pieces.emplace_back(p);
}