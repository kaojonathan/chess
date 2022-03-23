#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "rook.h"
using namespace std;

Rook::Rook(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		representation = "R"
	}
	else {

		representation = "r"
	}
}


void Rook::print() override {
	cout << representation;
}

string Rook::getRep() override {
	return representation;
}

void Rook::attach(Board* board) override {
	gameBoard = board;
}

void Rook::updateMovePossibilities() override {
	// get the cross
	for (int i = 1; i < 8; ++i) { // right
		if (x + i > 7) {
			break;
		}
		else {
			right.emplace_back(gameBoard->getPiece(x + i, y));
		}
	}

	for (int i = 1; i < 8; ++i) {
		if (x - i < 0) { // left
			break;
		}
		else {
			left.emplace_back(gameBoard->getPiece(x - i, y));
		}


	}
	for (int i = 1; i < 8; ++i) { // down
		if (y + i > 7) {
			break;
		}
		else {
			down.emplace_back(gameBoard->getPiece(x, y + i));
		}
	}

	for (int i = 1; i < 8; ++i) {
		if (y - i < 0) { // up
			break;
		}
		else {
			up.emplace_back(gameBoard->getPiece(x, y - i));
		}
	}
}