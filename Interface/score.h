#ifndef SCORE_H_
#define SCORE_H_
#include <vector>
class Score { // the score class (SCORE OF GAME)
	float wpoints = 0; // white's points
	float bpoints = 0; // black's points
public:
	void printScore(); // prints the score to output
	void whiteWin(); // adds a point to white
	void blackWin(); // adds a point to black
	void tie(); // adds half a point to both
};
#endif