#ifndef COMPUTER_H_
#define COMPUTER_H_
#include <vector>
// abstract class for the different AI levels

class Piece;
class Board;
class Player; // we need this?

class Computer {
    protected:
        int side; // 0 for white and 1 for black
        Board* gameBoard;
        std::vector<Piece*> pieces; // the computer's pieces
        std::vector<Piece*> enemypieces; // the opponent's pieces

        virtual void move() = 0;
        
    public:
        Computer(int);
        virtual ~Computer(); // needs implementation
        // asks computer player to make a move
        void computerMove() { 
            move();
        }
};

#endif
