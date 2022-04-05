#ifndef PROMOTIONCAP_H_
#define PROMOTIONCAP_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>

class PromotionCapture : public Move
{ // the promotioncapture class (a type of Move)
    std::string promoType; // the type of piece promoted
    std::string capType;  // the type of piece captured
public:
    PromotionCapture(int x1, int y1, int x2, int y2, std::string promoType, std::string capType);
    std::string getPromoType() override; // gets the promotion type
    std::string getCapType() override; // gets the capture type
};


#endif