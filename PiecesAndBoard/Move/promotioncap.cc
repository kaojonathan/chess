#include <string>
#include "promotioncap.h"
using namespace std;

PromotionCapture::PromotionCapture(int x1, int y1, int x2, int y2, std::string promoType, std::string capType): Move{x1, y1, x2, y2, "promocap"}, promoType{promoType}, capType{capType} {}

PromotionCapture::~PromotionCapture() {}

std::string PromotionCapture::getPromoType() {
    return promoType;
}

std::string PromotionCapture::getCapType() {
    return capType;
}