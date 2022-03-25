// DO NOT MODIFY THIS FILE
#ifndef QUEEN_H_
#define QUEEN_H_
#include "piece.h"
class Queen : public Piece {

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
    bool canMove(int x, int y) override;
    void updateMovePossibilities() override;
    bool kingInCheck(bool isWhite) override;



    // for the computer level 2 and 3 class
    pair<int, int> getCheckCoords() override;
    bool posInCheck(int x, int y) override;



};

#endif