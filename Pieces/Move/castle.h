#ifndef CASTLE_H_
#define CASTLE_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>

class Castle : public Move
{ // the castle class (a type of Move)
public:
    Castle(int x1, int y1, int x2, int y2); // constructor
    std::string getCapType() override { return "no"; } // gets the capture type
    std::string getPromoType() override { return "no"; } // gets the promotion type
};

#endif