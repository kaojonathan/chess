#ifndef QUEEN_H_
#define QUEEN_H_
#include "piece.h"
#include <vector>
class Queen : public Piece {

    // vectors extend from center of the piece
    std::vector<Piece*> upperLeftDiag; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> upperRightDiag; // positions that the piece can move to
    std::vector<Piece*> lowerLeftDiag; // positions that the piece can move to
    std::vector<Piece*> lowerRightDiag; // positions that the piece can move to

    std::vector<Piece*> up; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> right; // positions that the piece can move to
    std::vector<Piece*> down; // positions that the piece can move to
    std::vector<Piece*> left; // positions that the piece can move to
    int canMove(int x, int y) override;
    
public:
    Queen(bool isWhite);
    
    void updateMovePossibilities() override;
    bool kingInCheck(bool isWhite) override;



    // for the computer level 2 and 3 class
    pair<int, int> getCheckCoords() override;
    bool posInCheck(int x, int y) override;



};

#endif