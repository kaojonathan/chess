#include "player.h"

Player::Player(int side, int type) : side{side}, type{type} {}

Player::~Player() {}


void Player::kingCheckedBy(Piece * enemy) {
    opponentCheck = enemy;
}



