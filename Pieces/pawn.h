// DO NOT MODIFY THIS FILE
#ifndef PAWN_H_
#define PAWN_H_
#include "piece.h"

class Pawn : public Piece {
    int numMoves;

    // vectors extend from center of the piece
    // means down for black, up for white
    vector<Piece*> forward; // positions that the piece can move to (null means empty square!)
    // will always be size 1 after we move once!!! (b/c we can't move two squares after)


public:
    Pawn(bool isWhite);
    bool canMove(int x, int y) override;
    void prommote();
    void enPassant();
    void capture();
    void castling();
    void updateMovePossibilities() override; // did not implement yet since it is more complicated than the othersss
    bool kingInCheck(bool isWhite) override;
};

#endif