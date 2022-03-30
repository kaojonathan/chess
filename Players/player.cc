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

using namespace std;

Player::Player(int side, int type) : side{side}, type{type} {}


// initial player, use only when there is no setup
void Player::init(Board * board){
    gameBoard = board;
    int firstRow = (side == 0) ? 0 : 7;
    pieces.emplace_back(new Rook{side, 0, firstRow, gameBoard});
	pieces.emplace_back(new Knight{side, 1, firstRow, gameBoard});
	pieces.emplace_back(new Bishop{side, 2, firstRow, gameBoard});
	pieces.emplace_back(new Queen{side, 3, firstRow, gameBoard});
    king = new King{side, 4, firstRow, gameBoard};
    pieces.emplace_back(new Bishop{side, 5, firstRow, gameBoard});
    pieces.emplace_back(new Knight{side, 6, firstRow, gameBoard});
    pieces.emplace_back(new Rook{side, 7, firstRow, gameBoard});
    int secondRow = (side == 0) ? 1 : 6;
	for (int i = 0; i < 8; ++i){
		pieces.emplace_back(new Pawn{side, 5, secondRow, gameBoard});
	}
}

// get Piece for each players, only use after setup
void Player::claimPieces(){
    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 8; j += 1) {
            Piece *pc = gameBoard->getPiece(i, j);
            if (side == pc->getSide()) {
                if (pc->isKing()) king = pc;
                else pieces.emplace_back(pc);
            } 
        }
    }
}

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
        if (piece->getMoves.size() != 0 || piece->getTargets.size() != 0) return true;
    }
    if (king->getMoves.size() != 0 || king->getTargets.size() != 0) return true;
}


