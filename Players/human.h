// DO NOT MODIFY THIS FILE
#ifndef HUMAN_H_
#define HUMAN_H_
class Human : Piece {

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


