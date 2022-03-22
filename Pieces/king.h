#include "piece.h"
#ifndef KING_H_
#define KING_H_
class King : Piece {
    bool cancastle;
public:
    King(bool isWhite);
    ~King(bool isWhite);
    void move();
    void print() override;
};

#endif