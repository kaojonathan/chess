// DO NOT MODIFY THIS FILE
#ifndef PIECE_H_
#define PIECE_H_
class Piece {
    char x;
    int y;
    bool white;
    static int numWhiteKings;
    static int numBlackKings;
public:
    virtual void move() = 0;
    virtual bool check() = 0;
    virtual void print() = 0;
};

#endif