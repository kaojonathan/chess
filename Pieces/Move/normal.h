#ifndef NORMAL_H_
#define NORMAL_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>


class Normal : public Move {
    public:
        Normal(int x1, int y1, int x2, int y2);
        std::string getCapType() override {return "no";}
        std::string getPromoType() override {return "no";}

};

#endif