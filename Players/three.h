#ifndef THREE_H_
#define THREE_H_
#include "computer.h"

class Three : public Computer {

	void move() override;
	Three(int side, int level);
	~Three();

};



#endif