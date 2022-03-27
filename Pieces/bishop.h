// DO NOT MODIFY THIS FILE
#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"

using namespace std;

class Bishop : public Piece {


    // vectors extend from center of the piece
    std::vector<Piece*> upperLeftDiag; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> upperRightDiag; // positions that the piece can move to
    std::vector<Piece*> lowerLeftDiag; // positions that the piece can move to
    std::vector<Piece*> lowerRightDiag; // positions that the piece can move to
public:
    void updateMovePossibilities() override;
    bool kingInCheck(bool isWhite) override;
    Bishop(bool isWhite);
    // for the computer level 2 and 3 class
    pair<int, int> getCheckCoords() override;
    int posInCheck(int x, int y) override;
    bool isKing() override;
};

#endif