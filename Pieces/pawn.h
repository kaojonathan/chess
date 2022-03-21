// DO NOT MODIFY THIS FILE
#ifndef PAWN_H_
#define PAWN_H_
class Pawn : Piece {
    int numMoves;
public:
    void move();
    bool check();
    void prommote();
    void enPassant();
    void capture();
    void castling();


};

#endif