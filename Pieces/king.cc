#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "king.h"
using namespace std;

King::King(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		++numWhiteKings;
	}
	else {
		++numBlackKings;
	}
}

King::~King() {
	if (isWhite) {
		--numWhiteKings;
	}
	else {
		--numBlackKings;
	}
}

void King::print() override {
	if (isWhite) {
		cout << 'K';
	}
	else {
		cout << 'k';
	}
}