#include "one.h"
#include "board.h"
using namespace std;


One::One(int side) : Computer{ side } {}

void One::move() {
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
