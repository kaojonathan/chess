#ifndef KING_H_
#define KING_H_
#include "piece.h"

class King : public Piece {
    bool cancastle;

    // EITHER SIZE 0 or 1 (0 means no piece nor cell, null means empty square!)
    std::vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> upright; // positions that the piece can move to
    std::vector<Piece*> right; // positions that the piece can move to
    std::vector<Piece*> downright; // positions that the piece can move to
    std::vector<Piece*> down; // positions that the piece can move to
    std::vector<Piece*> downleft; // positions that the piece can move to
    std::vector<Piece*> left; // positions that the piece can move to
    std::vector<Piece*> upleft; // positions that the piece can move to
    int canMove(int x, int y) override;
    void updateMovePossibilities() override;

    // do nothing for king
    bool posInCheck(int, int) override;
    std::pair<int, int> getCheckCoords() override;
    bool kingInCheck() override; 

public:
    King(bool isWhite);
    ~King();
};

#endif