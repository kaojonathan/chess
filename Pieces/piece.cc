#include <string>
#include "piece.h"
using namespace std;

Piece::Piece(bool isWhite) : side{isWhite ? 0 : 1} {}

void Piece::setPos(int row, int col) {
	x = row;
	y = col;
}

string Piece::getRep() {
	return representation;
}


void Piece::attach(Board* board) {
	gameBoard = board;
}

// 0: white, 1: black
int Piece::getSide() {
	return side;
}

int Piece::getX() {
	return x;
}

int Piece::getY() {
	return y;
}


vector<int[2]> Piece::getCheckRoute() { return checkRoute; }

void Piece::forcedBy(Piece * enemyPiece) {
	forced = enemyPiece;
}