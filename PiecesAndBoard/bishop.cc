#include <string>
#include <vector>
#include <utility>
#include "bishop.h"
#include "board.h"
#include "piece.h"
using namespace std;

Bishop::Bishop(bool isWhite) : Piece{isWhite} {
	value = 5;
	if (isWhite) {
		representation = "B";
	}
	else {
		representation = "b";
	}
}


// NEW! update fields moves, attacks, checkRoute
void Bishop::updateMovePossibilities() {
	updateStatus(1);
}

// check if the emeny king is checked
// edit now it is not pure virtual

// attempts to move the bishop
// if successful, will update the position 
// [Edit: updating the position should be implemented by a board/player/main method, so that the board can check if the move is invalid and ask player to enter the correct comment. This method can only return the validity of the move, cannot move the piece. edit2: now it is not pure virtual]


// helper function that determines of the bishop in position (x, y) checks the king
bool Bishop::posInCheck(int col, int row) {
	return dScan(col, row, 1)->isKing();
}
