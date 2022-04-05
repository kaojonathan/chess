#include <string>
#include <vector>
#include <utility>
#include "rook.h"
#include "../Board/board.h"
using namespace std;

Rook::Rook(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 5;
	representation = (side == 0) ? "R" : "r";
}

// normal status update, assuming it is not forced
void Rook::nUpdate() {
	updateStatus = 1;
	dirScan(2);
}


// return a list of piece that it can attack if it is at position at and not forced
std::vector<Piece *> Rook::attackable(std::pair<int, int> at){
	return dScan(at, 2);
}
