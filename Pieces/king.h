#ifndef KING_H_
#define KING_H_
#include "piece.h"
#include <vector>

class King : public Piece {
    // normal update
    void nUpdate() override;
public:
    // constructor
    King(int side, int x, int y, Board * board);
    // return a list of piece that it can attack if it is at position at and not forced
    std::vector<Piece *> attackable(std::pair<int, int> at) override;
    // get all basic positions on the board that the king can move to
    std::vector<std::pair<int,int>> getPos(int x, int y);
};

#endif