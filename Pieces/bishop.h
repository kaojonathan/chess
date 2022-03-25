// DO NOT MODIFY THIS FILE
#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"

using namespace std;

class Bishop : public Piece {


    // vectors extend from center of the piece
    vector<Piece*> upperLeftDiag; // positions that the piece can move to (null means empty square!)
    vector<Piece*> upperRightDiag; // positions that the piece can move to
    vector<Piece*> lowerLeftDiag; // positions that the piece can move to
    vector<Piece*> lowerRightDiag; // positions that the piece can move to

public:
    Bishop(bool isWhite);
    int canMove(int x, int y) override;
    void updateMovePossibilities() override;
    std::string representation() override;
    bool kingInCheck(bool isWhite) override;



};

#endif