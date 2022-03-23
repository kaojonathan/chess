// DO NOT MODIFY THIS FILE
#ifndef PIECE_H_
#define PIECE_H_
using namespace std;
#include "board.h"
class Piece {
    int x; // use regular matrix coordinates (easier)
    int y;
    string representation;
    Board* gameBoard;
public:
    virtual void attach(Board* board) = 0;
    virtual void move() = 0;
    virtual bool check() = 0;
    virtual void print() = 0;
    virtual string getRep() = 0;
    void setPos(int row, int col);
    void updateMovePossibilities() = 0;
};

#endif