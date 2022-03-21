#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <rook.h>
using namespace std;

Rook::Rook(bool isWhite) : isWhite{ isWhite } {}


void Rook::print() override {
	if (isWhite) {
		cout << 'R'
	}
	else {
		cout << 'r';
	}
}