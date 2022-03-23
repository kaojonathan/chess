// DO NOT MODIFY THIS FILE
#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"

using namespace std;

class Bishop : Piece {


    // vectors extend from center of the piece
    vector<Piece*> upperLeftDiag; // positions that the piece can move to (null means empty square!)
    vector<Piece*> upperRightDiag; // positions that the piece can move to
    vector<Piece*> lowerLeftDiag; // positions that the piece can move to
    vector<Piece*> lowerRightDiag; // positions that the piece can move to

public:
    Bishop(bool isWhite);
    void attach(Board* board) override;
    void move() override;
    bool check() override;
    void print() override;
    string getRep() override;
    void updateMovePossibilities() override;



};

#endif