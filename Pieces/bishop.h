// DO NOT MODIFY THIS FILE
#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"
class Bishop : Piece {
public:
    Bishop(bool isWhite);
    void move();
    bool check();
    void print() override;
};

#endif