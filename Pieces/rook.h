// DO NOT MODIFY THIS FILE
#ifndef ROOK_H_
#define ROOK_H_
class Rook : Piece {
public:
    void move();
    bool check();
    void castling();
};

#endif