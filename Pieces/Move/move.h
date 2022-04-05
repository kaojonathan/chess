#ifndef MOVE_H_
#define MOVE_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


class Move {
    int pos1x;
    int pos1y;
    int pos2x;
    int pos2y;
    std::string type; // normal, capture, castle, promotion, promocap

virtual std::string getPromoType() = 0;
virtual std::string getCapType() = 0;

    public:
    Move(int x1, int y1, int x2, int y2, std::string type);
    virtual ~Move() = 0;
    std::string getType();
    int getPos1x();
    int getPos1y();
    int getPos2x();
    int getPos2y();
    std::string getPT() {
        return getPromoType();
    }
    std::string getCT() {
        return getCapType();
    }


};

#endif