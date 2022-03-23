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
    virtual void attach(Board* board) = 0;
    virtual void move() = 0;
    virtual bool check() = 0;
    virtual void print() = 0;
    virtual string getRep() = 0;
public:
    void setPos(int row, int col);
    virtual void updateMovePossibilities() = 0; // ? whats this
};

#endif