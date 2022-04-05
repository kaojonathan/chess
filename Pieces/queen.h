#ifndef QUEEN_H_
#define QUEEN_H_
#include "piece.h"
#include <vector>
class Queen : public Piece {
    // normal update
    void nUpdate() override;
public:
    // constructor
    Queen(int side, int x, int y, Board * board);
    // return a list of piece that it can attack if it is at position at and not forced
    std::vector<Piece *> attackable(std::pair<int, int>) override;
};

#endif