#include "computer.h"
using namespace std;
#include <string>

// constructor
Computer::Computer(int side, int level): Player{side, 1}, level{level} {}

// destructor
Computer::~Computer(){}
