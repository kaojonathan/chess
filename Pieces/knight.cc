#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "knight.h"
using namespace std;

Knight::Knight(bool isWhite) : white{ isWhite } {}


void Knight::print() override {
	if (isWhite) {
		cout << 'N';
	}
	else {
		cout << 'n';
	}
}