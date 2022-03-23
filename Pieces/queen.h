// DO NOT MODIFY THIS FILE
#ifndef QUEEN_H_
#define QUEEN_H_
#include "piece.h"
class Queen : Piece {

    // vectors extend from center of the piece
    vector<Piece*> upperLeftDiag; // positions that the piece can move to (null means empty square!)
    vector<Piece*> upperRightDiag; // positions that the piece can move to
    vector<Piece*> lowerLeftDiag; // positions that the piece can move to
    vector<Piece*> lowerRightDiag; // positions that the piece can move to

    vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    vector<Piece*> right; // positions that the piece can move to
    vector<Piece*> down; // positions that the piece can move to
    vector<Piece*> left; // positions that the piece can move to

public:
    Queen(bool isWhite);
    void move();
    bool check();
    string getRep() override;
    void print() override;
    void attach(Board* board) override;
    void updateMovePossibilities() override;
};

#endif