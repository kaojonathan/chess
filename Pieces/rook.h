// DO NOT MODIFY THIS FILE
#ifndef ROOK_H_
#define ROOK_H_
class Rook : Piece {
public:
    Rook(bool isWhite);
    bool move(char x, int y);
    bool check();
    void castling();
    void print() override;
};

#endif