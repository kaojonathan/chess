#include <string>
#include <vector>
#include <utility>
#include "queen.h"
#include "board.h"
#include "piece.h"
using namespace std;

Queen::Queen(bool isWhite) : Piece{ isWhite } {
	value = 9;
	if (isWhite) {
		representation = "Q";
	}
	else {
		representation = "q";
	}
}


void Queen::updateMovePossibilities()  {
	updateStatus(3);
}

// helper function that determines of the queen in position (x, y) checks the king
bool Queen::posInCheck(int col, int row) {
	return dScan(col, row, 3)->isKing();
}
