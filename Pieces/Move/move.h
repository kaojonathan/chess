#ifndef MOVE_H_
#define MOVE_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Move
{                     // the move class; for the chess moves in the game
    int pos1x;        // start x pos
    int pos1y;        // start y pos
    int pos2x;        // end x pos
    int pos2y;        // end y pos
    std::string type; // type of the Move: normal, capture, castle, promotion, promocap
    virtual std::string getPromoType() = 0; // gets the promotion type
    virtual std::string getCapType() = 0; // gets the capture type
public:
    Move(int x1, int y1, int x2, int y2, std::string type); // constructor
    virtual ~Move() = 0; // destructor
    std::string getType(); // gets the type of the move
    int getPos1x(); // gets the start x pos
    int getPos1y(); // gets the start y pos
    int getPos2x(); // gets the end x pos
    int getPos2y(); // gets the end y pos
    std::string getPT()
    { // gets the promotion type
        return getPromoType();
    }
    std::string getCT()
    { // gets the capture type
        return getCapType();
    }
};

#endif