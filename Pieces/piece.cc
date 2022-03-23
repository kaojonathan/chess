#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "piece.h"
using namespace std;

void Piece::setPos(int row, int col) {
	x = row;
	y = col;
}