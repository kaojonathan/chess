#ifndef THREE_H_
#define THREE_H_
#include "computer.h"

class Three : public Computer {

	std::pair<int, std::string> move(int &, int &, int &, int &) override;
public:
	Three(int side, int level);

};



#endif