#include <string>
#include "enpassant.h"
using namespace std;

EnPassant::EnPassant(int x1, int y1, int x2, int y2, Piece *cap): Move{x1, y1, x2, y2, "enpassant"}, captured{cap} {}

Piece * EnPassant::getCapPiece() {
    return captured;
}