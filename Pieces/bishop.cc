#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "bishop.h"
using namespace std;

Bishop::Bishop(bool isWhite) : white{ isWhite } {}

void Bishop::print() override {
	if (isWhite) {
		cout << 'B';
	} else {
		cout << 'b';
	}
}