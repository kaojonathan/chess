#include <string>
#include <vector>
#include <utility>
#include "queen.h"
#include "../Board/board.h"
#include "piece.h"
using namespace std;

Queen::Queen(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 9;
	representation = (side == 0) ? "Q" : "q";
}

// normal status update
void Queen::nUpdate()  {
	updateStatus = 1;
	dirScan(3);
}


// return a list of piece that it can attack if it is at position at and not forced
std::vector<Piece *> Queen::attackable(std::pair<int, int> at){
	return dScan(at, 3);
}