#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "piece.h"
#include <vector>
class Knight : public Piece {
    /* DEBUG
    // EITHER SIZE 0 or 1 (0 means no piece nor cell, null means empty square!)
    std::vector<Piece*> leftoneuptwo; // positions that the piece can move to (null means empty square!)
    std::vector<Piece*> rightoneuptwo; // positions that the piece can move to
    std::vector<Piece*> uponerighttwo; // positions that the piece can move to
    std::vector<Piece*> downonerighttwo; // positions that the piece can move to
    std::vector<Piece*> rightonedowntwo; // positions that the piece can move to
    std::vector<Piece*> leftonedowntwo; // positions that the piece can move to
    std::vector<Piece*> downonelefttwo; // positions that the piece can move to
    std::vector<Piece*> uponelefttwo; // positions that the piece can move to
    */
   void nUpdate() override;

public:
    Knight(int side, int x, int y, Board * board);
    
    // get a list of positions that he knight at (col, row) can move to, positions cannot be out of bound 
    std::vector<std::pair<int,int>> getPos(int col, int row);

/* DEBUG
    // for the computer level 2 and 3 class
    std::pair<int, int> getCheckCoords() override;
*/
    std::vector<Piece *> attackable(std::pair<int,int>) override;
};

#endif