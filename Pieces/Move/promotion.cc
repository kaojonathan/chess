#include <string>
#include "promotion.h"
using namespace std;

// constructor
Promotion::Promotion(int x1, int y1, int x2, int y2, string promoType): Move{x1, y1, x2, y2, "promotion"}, promoType{promoType} {}

// gets the promotion type
string Promotion::getPromoType() {
    return promoType;
}