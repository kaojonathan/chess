#ifndef ROOK_H_
#define ROOK_H_
#include "piece.h"


class Rook : public Piece {

// vectors extend from center of the piece
// edit: may not be needed anymore
/*
    std::vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> right; // positions that the piece can move to
    std::vector<Piece*> down; // positions that the piece can move to
    std::vector<Piece*> left; // positions that the piece can move to
*/

public:
    Rook(bool isWhite);
    // edit: show be implemented in player/board class, which contain the position of the king and the rook
    /* void castling(); */
    // for the computer level 2 and 3 class
    // edit: may not be useful anymore
    /* std::pair<int, int> getCheckCoords() override; */
    void updateMovePossibilities() override;
    bool posInCheck(int x, int y) override;
};

#endif