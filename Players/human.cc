#include "human.h"
using namespace std;

Human::Human(int side): Player{side, 0} {}

Human::~Human(){}


/*
# return 0 if ask for different move (move failed)
# return 1 if move was successful (ask for next move)
# return 2 if game is over
*/
int Human::playerMove() {

}