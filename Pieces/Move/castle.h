#ifndef CASTLE_H_
#define CASTLE_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>


class Castle : public Move {
    public:

        Castle(int x1, int y1, int x2, int y2);
        std::string getCapType() override {return "no";}
        std::string getPromoType() override {return "no";}
};

#endif