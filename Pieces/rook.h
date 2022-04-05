#ifndef ROOK_H_
#define ROOK_H_
#include "piece.h"


class Rook : public Piece {
    // normal update
    void nUpdate() override;
public:
    // constructor
    Rook(int side, int x, int y, Board * board);
    // return a list of piece that it can attack if it is at position at and not forced
    std::vector<Piece *> attackable(std::pair<int, int>) override;
};

#endif