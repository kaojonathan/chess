// DO NOT MODIFY THIS FILE
#ifndef QUEEN_H_
#define QUEEN_H_
class Queen : Piece {
public:
    Queen(bool isWhite);
    void move();
    bool check();
    void print() override;
};

#endif