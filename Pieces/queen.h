#ifndef QUEEN_H_
#define QUEEN_H_
#include "piece.h"
#include <vector>
class Queen : public Piece {
    // seems like we don't need the field anymore
/* DEBUG
    // vectors extend from center of the piece
    std::vector<Piece*> upperLeftDiag; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> upperRightDiag; // positions that the piece can move to
    std::vector<Piece*> lowerLeftDiag; // positions that the piece can move to
    std::vector<Piece*> lowerRightDiag; // positions that the piece can move to

    std::vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> right; // positions that the piece can move to
    std::vector<Piece*> down; // positions that the piece can move to
    std::vector<Piece*> left; // positions that the piece can move to
*/
    void nUpdate() override;
public:
    Queen(int side, int x, int y, Board * board);
    
    std::vector<Piece *> attackable(std::pair<int, int>) override;
};

#endif