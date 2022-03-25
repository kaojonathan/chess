#ifndef PIECE_H_
#define PIECE_H_
#include <string>

class Board;

class Piece {
    protected:
    int x;
    int y;
    int side; // 0 for white and 1 for black
    Board* gameBoard;
    // determine if the Piece can move to position (x,y), 0: no, 1: move, 2: capture
    virtual int canMove(int x, int y) = 0;
    // updates possible moves
    virtual void updateMovePossibilities() = 0; 
    // if the piece is checking the king
    virtual bool kingInCheck(bool isWhite) = 0;
    virtual std::string representation() = 0;
    public:
    Piece(bool isWhite);
    void setPos(int row, int col);
    void attach(Board* board);
    bool move(int x, int y);
    int getSide();
    std::string getRep();
};

#endif