#ifndef QUEEN_H_
#define QUEEN_H_
#include "piece.h"
#include <vector>
class Queen : public Piece {

    void nUpdate() override;
public:
    Queen(int side, int x, int y, Board * board);
    
    std::vector<Piece *> attackable(std::pair<int, int>) override;
};

#endif