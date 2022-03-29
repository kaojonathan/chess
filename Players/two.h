#ifndef TWO_H_
#define TWO_H_
#include "computer.h"

class Two : public Computer {

	void move() override;
	Two(int side, int level);
	~Two();

};



#endif