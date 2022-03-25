#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "piece.h"

class Knight : public Piece {

    // EITHER SIZE 0 or 1 (0 means no piece nor cell, null means empty square!)
    std::vector<Piece*> leftoneuptwo; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> rightoneuptwo; // positions that the piece can move to
    std::vector<Piece*> uponerighttwo; // positions that the piece can move to
    std::vector<Piece*> downonerighttwo; // positions that the piece can move to
    std::vector<Piece*> rightonedowntwo; // positions that the piece can move to
    std::vector<Piece*> leftonedowntwo; // positions that the piece can move to
    std::vector<Piece*> downonelefttwo; // positions that the piece can move to
    std::vector<Piece*> uponelefttwo; // positions that the piece can move to

public:
    Knight(bool isWhite);
    bool canMove(int x, int y) override;
    void updateMovePossibilities() override;
    bool kingInCheck(bool isWhite) override;



    // for the computer level 2 and 3 class
    pair<int, int> getCheckCoords() override;
    bool posInCheck(int x, int y) override;


};

#endif