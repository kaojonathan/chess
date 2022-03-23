#include "piece.h"
#ifndef KING_H_
#define KING_H_
class King : Piece {
    bool cancastle;


    // EITHER SIZE 0 or 1 (0 means no piece nor cell, null means empty square!)
    vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    vector<Piece*> upright; // positions that the piece can move to
    vector<Piece*> right; // positions that the piece can move to
    vector<Piece*> downright; // positions that the piece can move to
    vector<Piece*> down; // positions that the piece can move to
    vector<Piece*> downleft; // positions that the piece can move to
    vector<Piece*> left; // positions that the piece can move to
    vector<Piece*> upleft; // positions that the piece can move to

public:
    King(bool isWhite);
    ~King();
    void move();
    void updateMovePossibilities() override;
};

#endif