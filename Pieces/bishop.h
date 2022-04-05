#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"

using namespace std;

class Bishop : public Piece {
    /* DEBUG
    // vectors extend from center of the piece
    std::vector<Piece*> upperLeftDiag; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> upperRightDiag; // positions that the piece can move to
    std::vector<Piece*> lowerLeftDiag; // positions that the piece can move to
    std::vector<Piece*> lowerRightDiag; // positions that the piece can move to
    */
   void nUpdate() override;
public:
    
    Bishop(int side, int x, int y, Board * board);
    std::vector<Piece *> attackable(std::pair<int, int> at) override;
};

#endif