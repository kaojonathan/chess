#ifndef TWO_H_
#define TWO_H_
#include "computer.h"

class Two : public Computer {

	std::pair<int, std::string> move(int &, int &, int & ,int &) override;
public:
	Two(int side, int level);

};



#endif