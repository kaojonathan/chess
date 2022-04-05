// DO NOT MODIFY THIS FILE
#ifndef PAWN_H_
#define PAWN_H_
#include "piece.h"

class Pawn : public Piece {

    // vectors extend from center of the piece
    // means down for black, up for white
    std::vector<Piece*> forward; // positions that the piece can move to (null means empty square!)
    // will always be size 1 after we move once!!! (b/c we can't move two squares after)
    // update status, assuming that it is not forced
    void nUpdate() override;
public:
    // constructor
    Pawn(int side, int x, int y, Board *);
    // return the forward direction, either 1 or -1
    int frDir();
    // return a list of piece that it can attack if it is at position at and not forced
    std::vector<Piece *> attackable(std::pair<int, int> at) override;
};

#endif