#include "player.h"
#include "../PiecesAndBoard/board.h"
#include "../PiecesAndBoard/piece.h"
#include <utility>

using namespace std;

Player::Player(int side, int type) : side{side}, type{type} {}

Player::~Player() {}


void Player::kingCheckedBy(Piece * enemy) {
    opponentCheck = enemy;
    for (auto piece : pieces) piece->forcedBy(enemy, true);
}

void Player::removePiece(std::pair<int,int> pos) {// removes the piece in position (x, y) and places it in inactivePieces.

    for (int i = 0; i < pieces.size(); ++i) {
        if ((pieces[i]->getX() == pos.first) && (pieces[i]->getY() == pos.second)) {
            inactivePieces.emplace_back(pieces[i]); // emplace
            auto it = pieces.begin() + i;
            it = pieces.erase(it); // remove
        }
    }
}

// update status of all pieces of the player, return 0 if there is avaliable move for player, 1 if it is a checkmate, 2 if it is a draw.
int Player::checkStatus(){
    for (auto piece : pieces) piece->statusUpdate();
    king->statusUpdate();           // not sure if we need to do this with two kings together
    if (canMove()) return 0;        // the player can move a piece
    if (opponentCheck) return 1;    // checkmate
    return 2;
}

// unset that status fields of each piece
void Player::unsetStatus(){
    for (auto piece : pieces) piece->needsUpdate();
    king->needsUpdate();
}

// find all piece of Player can attack position pos
vector<Piece *> Player::canAttack(pair<int, int> pos){
    vector<Piece *> res{};
    if (king->canAttack(pos)) res.emplace_back(king);
    for(auto piece : pieces) {
        if (piece->canAttack(pos)) res.emplace_back(piece);
    }
    return res;
}

// true if there is any pieces that the player can move
bool Player::canMove() {
    for (auto piece : pieces){
        if ((piece->getMoves().size() != 0) || (piece->getTargets().size() != 0)) return true;
    }
    if ((king->getMoves().size() != 0) || (king->getTargets().size() != 0)) return true;
}


