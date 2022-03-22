#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "pawn.h"
using namespace std;

Pawn::Pawn(bool isWhite) : white{ isWhite } {}


void Pawn::print() override {
	if (isWhite) {
		cout << 'P'
	}
	else {
		cout << 'p';
	}
}