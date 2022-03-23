// DO NOT MODIFY THIS FILE
#ifndef ROOK_H_
#define ROOK_H_
#include "piece.h"
class Rook : Piece {

// vectors extend from center of the piece
    vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    vector<Piece*> right; // positions that the piece can move to
    vector<Piece*> down; // positions that the piece can move to
    vector<Piece*> left; // positions that the piece can move to


public:
    Rook(bool isWhite);
    bool move(char x, int y);
    bool check();
    string getRep() override;
    void castling();
    void print() override;
    void attach(Board* board) override;
    void updateMovePossibilities() override;
};

#endif