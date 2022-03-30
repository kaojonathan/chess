#include "player.h"
#include "board.h"

Player::Player(int side, int type) : side{side}, type{type} {}

Player::~Player() {}


void Player::kingCheckedBy(Piece * enemy) {
    opponentCheck = enemy;
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



