#include "score.h"
#include <iostream>
using namespace std;

// prints the score to output
void Score::printScore() {
	cout << "Final Score:" << endl;
	cout << "White: " << wpoints << endl;
	cout << "Black: " << bpoints << endl;
}

// adds a point to white
void Score::whiteWin() {
	++wpoints;
}

// adds a point to black
void Score::blackWin() {
	++bpoints;
}

// adds half a point to both
void Score::tie() {
	wpoints = wpoints + 0.5;
	bpoints = bpoints + 0.5;
}