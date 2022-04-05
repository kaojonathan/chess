#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"

using namespace std;

class Bishop : public Piece {

   void nUpdate() override;
public:
    
    Bishop(int side, int x, int y, Board * board);
    std::vector<Piece *> attackable(std::pair<int, int> at) override;
};

#endif