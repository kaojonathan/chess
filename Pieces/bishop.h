#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"

using namespace std;

class Bishop : public Piece {
    // normal update
    void nUpdate() override;
public:
    // constructor
    Bishop(int side, int x, int y, Board * board);
    // return a list of piece that it can attack if it is at position at and not forced
    std::vector<Piece *> attackable(std::pair<int, int> at) override;
};

#endif