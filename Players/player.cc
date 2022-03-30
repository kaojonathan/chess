#include "player.h"
#include "board.h"
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


void Player::checkStatus(){
    for (auto piece : pieces) piece->statusUpdate();
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

