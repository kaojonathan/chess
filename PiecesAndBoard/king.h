#ifndef KING_H_
#define KING_H_
#include "piece.h"

class King : public Piece {
    bool cancastle;
    /*
    // EITHER SIZE 0 or 1 (0 means no piece nor cell, null means empty square!)
    std::vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> upright; // positions that the piece can move to
    std::vector<Piece*> right; // positions that the piece can move to
    std::vector<Piece*> downright; // positions that the piece can move to
    std::vector<Piece*> down; // positions that the piece can move to
    std::vector<Piece*> downleft; // positions that the piece can move to
    std::vector<Piece*> left; // positions that the piece can move to
    std::vector<Piece*> upleft; // positions that the piece can move to
    */
    void fUpdate(Piece *) override;
    void nUpdate() override;

    /* std::pair<int, int> getCheckCoords() override; */

public:
    std::vector<Piece *> attackable(std::pair<int, int> at);
    King(bool isWhite);
    ~King();
};

#endif