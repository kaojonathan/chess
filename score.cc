#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <score.h>
using namespace std;

void Score::printScore() {
	cout << "Final Score:" << endl;
	cout << "White: " << wpoints << endl;
	cout << "Black: " << bpoints << endl;
}
void Score::whiteWin() {
	++wpoints;
}
void Score::blackWin() {
	++bpoints;
}
void Score::tie() {
	wpoints = wpoints + 0.5;
	bpoints = bpoints + 0.5;
}