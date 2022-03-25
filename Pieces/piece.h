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






    // added this (vincent) /// for computer level 2/3 class
    virtual pair<int, int> getCheckCoords() = 0; // returns the coordinate (x, y) that the piece can move to, to check the king, or (-1, -1) if no move is found

    virtual bool posInCheck(int x, int y) = 0; // determines of the piece in position (x, y) checks the king



    /////////////////



    public:
    Piece(bool isWhite);
    void setPos(int row, int col);
    void attach(Board* board);
    bool move(int x, int y);
    int getX();
    int getY();
    int getSide();
    std::string getRep();
};

#endif