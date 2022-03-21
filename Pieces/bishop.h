// DO NOT MODIFY THIS FILE
#ifndef BISHOP_H_
#define BISHOP_H_
class Bishop : Piece {
    bool isWhite;
public:
    Bishop(bool isWhite);
    void move();
    bool check();
    void print() override;
};

#endif