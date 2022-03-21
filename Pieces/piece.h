// DO NOT MODIFY THIS FILE
#ifndef PIECE_H_
#define PIECE_H_
class Piece {
    char x;
    int y;
    char player;
    bool cap;
    int point;
public:
    virtual void move() = 0;
    virtual bool check() = 0;
    virtual void print() = 0;
};

#endif