#include <iostream>
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

void Piece::setPos(int row, int col) {
	x = row;
	y = col;
}


string getRep() {
	return representation;
}


void print() {
	cout << representation;
}

void attach(Board* board) {
	gameBoard = board;
}