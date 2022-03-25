#include "two.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
using namespace std;

void Two::move() {

	// shuffle the array first (using some way)


	for (int i = 0; i < pieces.size(); ++i) {
		pair<int, int> checkCoords = getCheckCoords(pieces[i]);
		// potential check x and y position (-1, -1) if there is none (need to implement this)

		if (checkCoords.first != -1) { // if the piece can check

			gameBoard->movePiece(pieces[i]->getX(), pieces[i]->getY(), checkCoords.first, checkCoords.second); // move it


		}


	}


	// if no piece can check, check for a capture


	for (int i = 0; i < pieces.size(); ++i) {
		if (canCapture(pieces[i])) { // if the piece can capture (need to implement this)

			gameBoard->movePiece(pieces[i]->getX(), pieces[i]->getY(), canCapture(pieces[i])->getX(), canCapture(pieces[i])->getY());
		



		}

	}

	// otherwise randomize the move

	bool madeMove = false;

	while (!madeMove) { // keep looping if we haven't made a move



		// randomly chooses from the type of pieces which one to move (there are 

		int randNum = rand() % pieces.size(); // randomly gives us a number from 0 to number of pieces - 1


		int randomX = rand() % 8; // randomly give us an x-coordinate


		int randomY = rand() % 8; // randomly give us a y-coordinate


		// check if the move is valid, then move it

		if (pieces[randNum]->canMove(randomX, randomY)) {
			gameBoard->movePiece(pieces[randNum]->getX(), pieces[randNum]->getY(), randomX, randomY);

			madeMove = true;
		}

		// otherwise keep looping (might be inefficient)
	}


}
