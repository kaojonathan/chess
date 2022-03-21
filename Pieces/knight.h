// DO NOT MODIFY THIS FILE
#ifndef KNIGHT_H_
#define KNIGHT_H_
class Knight : Piece {
public:
    Knight(bool isWhite);
    void move();
    bool check();
    void print() override;

};

#endif