#ifndef ROOK_H_
#define ROOK_H_
#include "piece.h"


class Rook : public Piece {


void nUpdate() override;
public:
    Rook(int side, int x, int y, Board * board);
    
    std::vector<Piece *> attackable(std::pair<int, int>) override;
};

#endif