#ifndef ENPASSANT_H_
#define ENPASSANT_H_

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "move.h"
#include <string>
#include <vector>

class EnPassant : public Move
{

public:
    EnPassant(int x1, int y1, int x2, int y2);
    ~EnPassant();
};

#endif