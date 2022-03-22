#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "queen.h"
using namespace std;

Queen::Queen(bool isWhite) : white{ isWhite } {}


void Queen::print() override {
	if (isWhite) {
		cout << 'Q'
	}
	else {
		cout << 'q';
	}
}