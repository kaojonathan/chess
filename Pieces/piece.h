#ifndef PIECE_H_
#define PIECE_H_
#include "board.h"
#include <string>

class Piece {
    int x; // use regular matrix coordinates (easier)
    int y;
    string representation;
    Board* gameBoard;
    void attach(Board* board);
    virtual bool canMove(int x, int y) = 0;
    std::string getRep();
public:
    void setPos(int row, int col);
    virtual void updateMovePossibilities() = 0; 
    virtual bool kingInCheck(bool isWhite) = 0;
};

#endif