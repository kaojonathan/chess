#include <string>
#include "promotioncap.h"
using namespace std;

PromotionCapture::PromotionCapture(int x1, int y1, int x2, int y2, string promoType, string capType): Move{x1, y1, x2, y2, "promocap"}, promoType{promoType}, capType{capType} {}



string PromotionCapture::getPromoType() {
    return promoType;
}

string PromotionCapture::getCapType() {
    return capType;
}