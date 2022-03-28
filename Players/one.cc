#include "one.h"
#include "board.h"
using namespace std;

One::One(int side) : Computer{side} {}

void One::move()
{
	bool madeMove = false;
	while (!madeMove)
	{ // keep looping if we haven't made a move
	int pieceIndex =  rand() % pieces.size(); // randomly give us an x-coordinate
		int i = rand() % 8; // randomly give us an x-coordinate
		int j = rand() % 8; // randomly give us a y-coordinate
				if (pieces[pieceIndex]->move(i, j) != 0)
				{ // if the move is valid then move it
					gameBoard->moveP(pieces[pieceIndex]->getX(), pieces[pieceIndex]->getY(), i, j);
					madeMove == true;
				}
		
		// otherwise keep looping (might be inefficient)
	}
}
