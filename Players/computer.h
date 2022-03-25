// DO NOT MODIFY THIS FILE
#ifndef COMPUTER_H_
#define COMPUTER_H_
class Board;
class Player;
class Computer {
    int side; // 0 for white and 1 for black
    Board* gameBoard;
    vector<Piece*> pieces; // the computer's pieces
    vector<Piece*> enemypieces; // the opponent's pieces

    void move() = 0;
    Computer(int side) = 0;
    ~Computer() = 0; // needs implementation

public:

};

#endif
