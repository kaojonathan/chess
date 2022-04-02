#include <string>
#include "promotion.h"
using namespace std;

Promotion::Promotion(int x1, int y1, int x2, int y2, std::string promoType): Move{x1, y1, x2, y2, "promotion"}, promoType{promoType} {}

Promotion::~Promotion() {}

std::string Promotion::getPromoType() {
    return promoType;
}