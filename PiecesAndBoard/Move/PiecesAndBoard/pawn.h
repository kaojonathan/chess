// DO NOT MODIFY THIS FILE
#ifndef PAWN_H_
#define PAWN_H_
#include "piece.h"

class Pawn : public Piece {

    // vectors extend from center of the piece
    // means down for black, up for white
    std::vector<Piece*> forward; // positions that the piece can move to (null means empty square!)
    // will always be size 1 after we move once!!! (b/c we can't move two squares after)

public:
    Pawn(int side, int x, int y, Board *);
    int frDir();            // return the forward direction, either 1 or -1 

    void prommote();
    void enPassant();
    void capture();
    void castling();
    void nUpdate() override; // update status, assuming that it is not forced
    std::vector<Piece *> attackable(std::pair<int, int> at) override;

    // for the computer level 2 and 3 class
    /*std::pair<int, int> getCheckCoords() override;*/

};

#endif