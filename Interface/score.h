#ifndef SCORE_H_
#define SCORE_H_
#include <vector>
class Score {
	float wpoints = 0;
	float bpoints = 0;
public:
	void printScore();
	void whiteWin();
	void blackWin();
	void tie();
};
#endif