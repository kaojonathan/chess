// DO NOT MODIFY THIS FILE
#ifndef PAWN_H_
#define PAWN_H_
#include "piece.h"
using namespace std;
class Pawn : Piece {
    int numMoves;

    // vectors extend from center of the piece
    // means down for black, up for white
    vector<Piece*> forward; // positions that the piece can move to (null means empty square!)
    // will always be size 1 after we move once!!! (b/c we can't move two squares after)


public:
    Pawn(bool isWhite);
    void move();
    bool check();
    void prommote();
    void enPassant();
    void capture();
    void castling();
    string getRep() override;
    void attach(Board* board) override;
    void print() override;
    void updateMovePossibilities() override; // did not implement yet since it is more complicated than the othersss
};

#endif