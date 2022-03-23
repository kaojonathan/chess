// DO NOT MODIFY THIS FILE
#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "piece.h"
class Knight : Piece {

    // EITHER SIZE 0 or 1 (0 means no piece nor cell, null means empty square!)
    vector<Piece*> leftoneuptwo; // positions that the piece can move to (null means empty square!)
    vector<Piece*> rightoneuptwo; // positions that the piece can move to
    vector<Piece*> uponerighttwo; // positions that the piece can move to
    vector<Piece*> downonerighttwo; // positions that the piece can move to
    vector<Piece*> rightonedowntwo; // positions that the piece can move to
    vector<Piece*> leftonedowntwo; // positions that the piece can move to
    vector<Piece*> downonelefttwo; // positions that the piece can move to
    vector<Piece*> uponelefttwo; // positions that the piece can move to

public:
    Knight(bool isWhite);
    void move();
    void updateMovePossibilities() override;
    bool kingInCheck(bool isWhite) override;
};

#endif