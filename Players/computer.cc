#include "computer.h"
using namespace std;
#include <string>

Computer::Computer(int side, int level): Player{side, 1}, level{level} {}

Computer::~Computer(){}
