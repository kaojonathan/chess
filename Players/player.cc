#include "player.h"
#include "board.h"
#include <utility>

using namespace std;

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


void Player::checkStatus(){
    for (auto piece : pieces) piece->statusUpdate();
}

// unset that status fields of each piece
void Player::unsetStatus(){
    for (auto piece : pieces) piece->needsUpdate();
}

// determine any piece of Player can attack position pos
bool Player::canAttack(pair<int, int> pos){
    for(auto piece : pieces) {
        if (piece->canAttack(pos)) return true;
    }
    return false;
}

