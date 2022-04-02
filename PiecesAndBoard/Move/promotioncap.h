#ifndef PROMOTIONCAP_H_
#define PROMOTIONCAP_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>

class PromotionCapture : public Move
{
    std::string promoType; // the type of piece promoted
    std::string capType;  // the type of piece captured

public:
    PromotionCapture(int x1, int y1, int x2, int y2, std::string promoType, std::string capType);
    ~PromotionCapture();
    std::string getPromoType() override;
    std::string getCapType() override;
};


#endif