#ifndef ONE_H_
#define ONE_H_
#include "computer.h"

class One : public Computer {

	void move() override;
	One(int side, int level);
	~One();

};



#endif