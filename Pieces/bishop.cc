#include <string>
#include <vector>
#include <utility>
#include "bishop.h"
#include "../Board/board.h"
#include "piece.h"
using namespace std;

// constructor
Bishop::Bishop(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 3;
	representation = (side == 0) ? "B" : "b";
}


// normal status update, assuming it is not forced
void Bishop::nUpdate() {
	updateStatus = 1;
	dirScan(1);
}

// return a list of piece that it can attack if it is at position at and not forced
std::vector<Piece *> Bishop::attackable(std::pair<int, int> at) {
	return dScan(at, 1);
}