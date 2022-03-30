#include "human.h"
using namespace std;

Human::Human(int side): Player{side, 0} {}

Human::~Human(){}


/*
# return 0 if ask for different move (move failed)
# return 1 if move was successful (ask for next move)
# return 2 if capture was sucessful (ask for next move)
*/
int Human::playerMove(int oldCol, int oldRow, int newCol, int newRow) {
    /*
    check if player owns the piecse
    let p be the piece pointer at pos1
        status = p.move(pos1)
        return status
    */
}