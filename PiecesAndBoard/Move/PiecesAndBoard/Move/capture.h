#ifndef CAPTURE_H_
#define CAPTURE_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>


class Capture : public Move {
    std::string capType;  // the type of piece captured



    public:
    Capture(int x1, int y1, int x2, int y2, std::string capType);
    ~Capture();
    std::string getCapType();
};

#endif