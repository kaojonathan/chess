#include <string>
#include "capture.h"
using namespace std;

Capture::Capture(int x1, int y1, int x2, int y2, string capType, Piece *cap): Move{x1, y1, x2, y2, "normal"}, capType{capType}, captured{cap} {}

Piece * Capture::getCapPiece() {
    return captured;
}

string Capture::getCapType() {
    return capType;
}