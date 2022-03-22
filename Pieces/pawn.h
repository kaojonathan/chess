// DO NOT MODIFY THIS FILE
#ifndef PAWN_H_
#define PAWN_H_
#include "piece.h"
class Pawn : Piece {
    int numMoves;
public:
    Pawn(bool isWhite);
    void move();
    bool check();
    void prommote();
    void enPassant();
    void capture();
    void castling();
    void print() override;
    
};

#endif