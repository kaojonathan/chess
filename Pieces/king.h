#ifndef KING_H_
#define KING_H_
#include "piece.h"
#include <vector>

class King : public Piece {

    void nUpdate() override;


public:
    std::vector<Piece *> attackable(std::pair<int, int> at) override;
    King(int side, int x, int y, Board * board);
    std::vector<std::pair<int,int>> getPos(int x, int y);
    ~King();
};

#endif