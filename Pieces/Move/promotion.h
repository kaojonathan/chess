#ifndef PROMOTION_H_
#define PROMOTION_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>

class Promotion : public Move
{ // the promotion class (a type of Move)
    std::string promoType; // the type of piece promoted
public:
    Promotion(int x1, int y1, int x2, int y2, std::string promoType);
    std::string getPromoType() override; // gets the promotion type
    std::string getCapType() override {return "no";} // gets the capture type
};


#endif