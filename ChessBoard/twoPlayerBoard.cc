#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include "twoPlayerBoard.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
using namespace std;

twoPlayerBoard::twoPlayerBoard() {}

twoPlayerBoard::origSetup{

	board[0][0] = new Rook(false);
board[0][1] = new Knight(false);
board[0][2] = new Bishop(false);
board[0][3] = new Queen(false);
board[0][4] = new King(false);
board[0][5] = new Bishop(false);
board[0][6] = new Knight(false);
board[0][7] = new Rook(false);

for (int i = 0; i < 8; ++i) {
	board[1][i] = new Pawn(false);
}

board[7][0] = new Rook(true);
board[7][1] = new Knight(true);
board[7][2] = new Bishop(true);
board[7][3] = new Queen(true);
board[7][4] = new King(true);
board[7][5] = new Bishop(true);
board[7][6] = new Knight(true);
board[7][7] = new Rook(true);

for (int i = 0; i < 8; ++i) {
	board[6][i] = new Pawn(true);
}

}

twoPlayerBoard::print() {
	for (int i = 0; i < 8; ++i) {
		cout << 8 - i << ' ';
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] == nullptr) { // empty tile
				if ((i + j) % 2) { // if sum is odd it's a white tile
					cout << ' ';
				}
				else { // otherwise it's a black tile

					cout << '_';
				}
			}
			else { // piece is on it
				board[i][j]->print();
			}
		}
		cout << endl;

	}
	cout << endl << "  ";
	for (int i = 0; i < 8; ++i) {
		cout << 'a' + i;
	}
	cout << endl;
}

void insertNewPiece(string validpiece, string position) {

	if (board[8 - (position[1] - '0')][position[0] - 'a']) {
		delete board[8 - (position[1] - '0')][position[0] - 'a'];
	}
	switch validpiece
	{
	case K:
			board[8 - (position[1] - '0')][position[0] - 'a'] = new King(true);
	case k:
		board[8 - (position[1] - '0')][position[0] - 'a'] = new King(false);

	case Q:

		board[8 - (position[1] - '0')][position[0] - 'a'] = new Queen(true);
	case q:


		board[8 - (position[1] - '0')][position[0] - 'a'] = new Queen(false);
	case R:


		board[8 - (position[1] - '0')][position[0] - 'a'] = new Rook(true);
	case r:

		board[8 - (position[1] - '0')][position[0] - 'a'] = new Rook(false);
	case B:
		board[8 - (position[1] - '0')][position[0] - 'a'] = new Bishop(true);
	case b:
		board[8 - (position[1] - '0')][position[0] - 'a'] = new Bishop(false);
	case N:

		board[8 - (position[1] - '0')][position[0] - 'a'] = new Knight(true);
	case n:
		board[8 - (position[1] - '0')][position[0] - 'a'] = new Knight(false);
	case P:

		board[8 - (position[1] - '0')][position[0] - 'a'] = new Pawn(true);
	case p:

		board[8 - (position[1] - '0')][position[0] - 'a'] = new Pawn(false);
	}
}

void removePiece(string position) {
	if (board[8 - (position[1] - '0')][position[0] - 'a']) {
		delete board[8 - (position[1] - '0')][position[0] - 'a'];
	}
}


bool verifySetup() { // NOT DONE
	int numWhiteKings = 0;
	int numBlackKings = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {




		}
	}




}