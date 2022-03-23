#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "pawn.h"
using namespace std;

Pawn::Pawn(bool isWhite) : white{ isWhite } {
	if (isWhite) {
		representation = "P"
	}
	else {

		representation = "p"
	}
}


void Pawn::print() override {
	cout << representation;
}

string Pawn::getRep() override {
	return representation;
}


void Pawn::attach(Board* board) override {
	gameBoard = board;
}

void Pawn::updateMovePossibilities() override {

	if (representation == "P") { // white

		if (numMoves < 1) {



			for (int i = 1; i < 3; ++i) {
				if (y - i < 0) { // up
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y - i));
				}
			}

		}
		else {

			for (int i = 1; i < 2; ++i) {
				if (y - i < 0) { // up
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y - i));
				}
			}



		}


	}
	else { // black

		if (numMoves < 1) {

			for (int i = 1; i < 3; ++i) { // down
				if (y + i > 7) {
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y + i));
				}
			}


		}
		else {
			for (int i = 1; i < 2; ++i) { // down
				if (y + i > 7) {
					break;
				}
				else {
					forward.emplace_back(gameBoard->getPiece(x, y + i));
				}
			}


		}


	}
}