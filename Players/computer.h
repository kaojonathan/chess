// DO NOT MODIFY THIS FILE
#ifndef COMPUTER_H_
#define COMPUTER_H_
class Board;
class Computer {

    Board* gameBoard;
    vector<Piece*> pieces; // the computer's pieces
    void move() = 0;

public:

};

#endif
