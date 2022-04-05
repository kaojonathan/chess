#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "piece.h"
#include <vector>
class Knight : public Piece {
    // normal update
    void nUpdate() override;
public:
    Knight(int side, int x, int y, Board * board);
    // get a list of positions that he knight at (col, row) can move to, positions cannot be out of bound 
    std::vector<std::pair<int,int>> getPos(int col, int row);
    // return a list of piece that it can attack if it is at position at and not forced
    std::vector<Piece *> attackable(std::pair<int,int>) override;
};

#endif