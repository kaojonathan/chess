#include "player.h"
#include "../PiecesAndBoard/board.h"
#include "../PiecesAndBoard/piece.h"
#include "../PiecesAndBoard/rook.h"
#include "../PiecesAndBoard/bishop.h"
#include "../PiecesAndBoard/king.h"
#include "../PiecesAndBoard/queen.h"
#include "../PiecesAndBoard/knight.h"
#include "../PiecesAndBoard/pawn.h"
#include <utility>
#include <iostream>

using namespace std;

Player::Player(int side, int type) : side{side}, pieces{vector<Piece*>{}}, inactivePieces{vector<Piece*>{}}, type{type} {}


// initial player, use only when there is no setup
void Player::init(Board * board, Player *player){
    gameBoard = board;
    opponent = player;
}

// get Piece for each players, only use after setup
void Player::claimPieces(){
    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 8; j += 1) {
            Piece *pc = gameBoard->getPiece(i, j);
	    if (pc) {
            if (side == pc->getSide()) {
                pc->setOpponent(opponent);
                if (pc->isKing()) king = pc;
                else pieces.emplace_back(pc);
            } 
          }
        }
    }
}


Player::~Player()
{
    while (pieces.size() > 0)
    {
        delete pieces.back();
        pieces.pop_back();
    }
    delete king;
}

void Player::kingCheckedBy(Piece *enemy)
{
    opponentCheck = enemy;
    for (auto piece : pieces)
        piece->forcedBy(enemy, true);
}

void Player::removePiece(std::pair<int, int> pos)
{ // removes the piece in position (x, y) and places it in inactivePieces.

    for (size_t i = 0; i < pieces.size(); ++i)
    {
        if ((pieces[i]->getX() == pos.first) && (pieces[i]->getY() == pos.second))
        {
            inactivePieces.emplace_back(pieces[i]); // emplace
            auto it = pieces.begin() + i;
            it = pieces.erase(it); // remove
        }
    }
}

// update status of all pieces of the player, return 0 if there is avaliable move for player, 1 if it is a checkmate, 2 if it is a draw.
int Player::checkStatus()
{
    for (auto piece : opponent->getPieces())
        piece->statusUpdate();
    for (auto piece : pieces)
        piece->statusUpdate();
    king->statusUpdate();
    if (canMove())
        return 0; // the player can move a piece
    if (opponentCheck)
        return 1; // checkmate
    return 2;
}

// unset that status fields of each piece
void Player::unsetStatus()
{
    for (auto piece : pieces)
        piece->needsUpdate();
    king->needsUpdate();
}

// find all piece of Player can attack position pos
vector<Piece *> Player::canAttack(pair<int, int> pos)
{
    vector<Piece *> res{};
    if (king->isUpdated() && king->canAttack(pos))
        res.emplace_back(king);
    for (auto piece : pieces)
    {
        if (piece->canAttack(pos))
            res.emplace_back(piece);
    }
    return res;
}

// true if there is any pieces that the player can move
bool Player::canMove()
{
    for (auto piece : pieces)
    {
        if ((piece->getMoves().size() != 0) || (piece->getTargets().size() != 0))
            return true;
    }
    if ((king->getMoves().size() != 0) || (king->getTargets().size() != 0))
        return true;
    return false;
}

// print players fields
void Player::print(){
    cout << king->getRep() << " at position (" << king->getX() << "," << king->getY() << endl; 
    for (auto piece : pieces) {
        if (!piece) cout << "something is wrong in Player::claimPieces()" << endl; 
        else cout << piece->getRep() << " at position (" << piece->getX() << "," << piece->getY() << endl; 
    }
}

void Player::addToPieces(Piece *p) {
    
pieces.emplace_back(p);


}