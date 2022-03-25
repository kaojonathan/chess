#include <string>
#include "piece.h"
using namespace std;

void Piece::setPos(int row, int col) {
	x = row;
	y = col;
}

string Piece::getRep() {
	return representation;
}

bool Piece::move(int x, int y) {
	return this->canMove(x,y);
}

void Piece::attach(Board* board) {
	gameBoard = board;
}

int Piece::getX() {
	return x;
}

int Piece::getY() {
	return y;
}