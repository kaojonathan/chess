#include <iostream>
#include <string>
#include <vector>
#include "knight.h"
using namespace std;

Knight::Knight(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		representation = "N"
	}
	else {

		representation = "n"
	}
}


void Knight::print() override {
	cout << representation;
}

string Knight::getRep() override {
	return representation;
}
void Knight::attach(Board* board) override {
	gameBoard = board;
}

void Knight::updateMovePossibilities() override {
	// knight's availible moves

	if ((x - 1 >= 0) && (y + 2 <= 7) {
		leftonedowntwo.emplace_back(gameBoard->getPiece(x - 1, y + 2));
	}

	if ((x - 1 >= 0) && (y - 2 >= 0) {
		leftoneuptwo.emplace_back(gameBoard->getPiece(x - 1, y - 2));
	}


	if ((x + 1 <= 7) && (y + 2 <= 7) {
		rightonedowntwo.emplace_back(gameBoard->getPiece(x + 1, y + 2));
	}

	if ((x + 1 <= 7) && (y - 2 >= 0) {
		rightoneuptwo.emplace_back(gameBoard->getPiece(x + 1, y - 2));
	}




	if ((x + 2 <= 7) && (y + 1 <= 7) {
		downonerighttwo.emplace_back(gameBoard->getPiece(x - 1, y + 2));
	}

	if ((x - 2 >= 0) && (y + 1 <= 7) {
		downonelefttwo.emplace_back(gameBoard->getPiece(x - 1, y - 2));
	}


	if ((x + 2 <= 7) && (y - 1 >= 0) {
		uponerighttwo.emplace_back(gameBoard->getPiece(x + 1, y + 2));
	}

	if ((x - 2 >= 0) && (y - 1 >= 0) {
		uponelefttwo.emplace_back(gameBoard->getPiece(x + 1, y - 2));
	}

}