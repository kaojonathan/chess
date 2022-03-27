#ifndef ROOK_H_
#define ROOK_H_
#include "piece.h"


class Rook : public Piece {

// vectors extend from center of the piece
    std::vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> right; // positions that the piece can move to
    std::vector<Piece*> down; // positions that the piece can move to
    std::vector<Piece*> left; // positions that the piece can move to
    int canMove(int x, int y) override;
    void updateMovePossibilities() override;

public:
    Rook(bool isWhite);
    void castling();
    bool kingInCheck(bool isWhite) override;

    // for the computer level 2 and 3 class
    pair<int, int> getCheckCoords() override;
    bool posInCheck(int x, int y) override;
    bool isKing() override;

};

#endif