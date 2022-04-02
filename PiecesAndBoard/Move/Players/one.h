#ifndef ONE_H_
#define ONE_H_
#include "computer.h"

class One : public Computer {

	std::pair<int, std::string> move() override;
public:
	One(int side, int level);

};



#endif