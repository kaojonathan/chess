// DO NOT MODIFY THIS FILE
#ifndef KING_H_
#define KING_H_
class King : Piece {
    bool cancastle;
public:
    King(bool isWhite);
    void move();
    bool check();
    void castling();
    void print() override;
};

#endif