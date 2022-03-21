// DO NOT MODIFY THIS FILE
#ifndef PIECE_H_
#define PIECE_H_
class Piece {
    char x;
    int y;
    char player;
    bool cap;
    int point;
public:
    void move();
    bool check();


};

#endif