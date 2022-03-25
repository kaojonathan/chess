#ifndef PIECE_H_
#define PIECE_H_
#include <string>

class Board;

class Piece {
    int x;
    int y;
    string representation;
    Board* gameBoard;

    virtual bool canMove(int x, int y) = 0;
    // updates possible moves
    virtual void updateMovePossibilities() = 0; 
    // if the piece is checking the king
    virtual bool kingInCheck(bool isWhite) = 0; 
public:
    void setPos(int row, int col);
    std::string getRep();
    void attach(Board* board);
};

#endif