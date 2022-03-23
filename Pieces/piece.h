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
    void attach(Board* board);
    virtual void move() = 0;
    void print();
    string getRep();
public:
    void setPos(int row, int col);
    virtual void updateMovePossibilities() = 0; // ? whats this // updates each Piece's possible moves
    virtual bool kingInCheck(bool isWhite) = 0;
};

#endif