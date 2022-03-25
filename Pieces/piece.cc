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



void Piece::attach(Board* board) {
	gameBoard = board;
}