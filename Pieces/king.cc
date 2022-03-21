#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <king.h>
using namespace std;

King::King(bool isWhite) : isWhite{ isWhite } {}

void King::print() override {
	if (isWhite) {
		cout << 'K';
	}
	else {
		cout << 'k';
	}
}