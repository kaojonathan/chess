#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "XWindowImpl.h"
#include "Game.h"
#include "window.h"
#include "board.h"
#include "twoPlayerBoard.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "score.h"
using namespace std;



/////////// HELPER FUNCTIONS /////////////////



// isComputer checks if the 'player' is a "computer". if it is, also updates level to give the level of the computer
bool isComputer(string player, int& level)
{
	if (player.substr(0, 8) == "computer")
	{
		if ((player[8] = '[') && (player[10] = ']')) {
			if ('1' <= player[9] && player[9] <= 4) {
				level = player[9];
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}


bool isValidPosition(string position) {
	if (position.length() == 2) {
		if (('a' <= position[0] <= 'h') && (1 <= position[1] <= 8)) {
			return true;
		}
	}
	else {
		return false;
	}
}

// used for set up to check if a piece has been specified correctly
bool isValidPiece(string piece) {
	if (piece.length() == 1) {
		return ((piece[0] == 'r') || (piece[0] == 'n') || (piece[0] == 'b') || 
				(piece[0] == 'q') || (piece[0] == 'k') || (piece[0] == 'p')	|| 
				(piece[0] == 'R') || (piece[0] == 'N') || (piece[0] == 'B') || 
				(piece[0] == 'Q') || (piece[0] == 'K') || (piece[0] == 'P'));
	}
}



// fills the graphic board at coordinate (x, y) with a blank tile (erases the piece)
void Game::fill(int x, int y) { 
	if ((x + y + 2) % 2) {
		window->fillRectangle(50 * (x + 1), 50 * (y + 1), 50, 50, XWindow::Cyan);
	}
	else {
		window->fillRectangle(50 * (x + 1), 50 * (y + 1), 50, 50, XWindow::White);
	}
}

 // draws a piece at coordinate (x, y) with piece string
void Game::drawPiece(string piece, int x, int y) {
	window->drawString(25 + (50 * (x + 1)), 25 + (50 * (y + 1)), piece);
} 

// setup: inserts a piece at given position
void Game::insertNewPiece(std::string validpiece, std::string position) {
	
	if (('0' <= position[1] <= '7') && ('a' <= position[0] <= 'h'))
	{
		if (validpiece == "K")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("K", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "k")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("k", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "Q")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("Q", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "q")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("q", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "R")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("R", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "r")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("r", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "B")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("B", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "b")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("b", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "N")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("N", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "n")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("n", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "P")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("P", position[0] - 'a', 8 - (position[1] - '0'));
		}
		else if (validpiece == "p")
		{
			if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
			{
				fill(position[0] - 'a', 8 - (position[1] - '0'));
			}
			drawPiece("p", position[0] - 'a', 8 - (position[1] - '0'));
		}
	}
}


void Game::removePiece(std::string position) {
	if (board->getPiece(position[0] - 'a',8 - (position[1] - '0')))
	{
		fill(position[0] - 'a', 8 - (position[1] - '0'));
	}
}


	
void Game::displayCheck(bool isWhite) {

	if (isWhite) {
		cout << "White is in check." << endl;

		window->drawString(10, 10, "White is in check.");
		sleep(3000);
		window->fillRectangle(9, 9, 200, 10, XWindow::White);

	} else {

		cout << "Black is in check." << endl;
					sleep(3000);
		window->fillRectangle(9, 9, 200, 10, XWindow::White);
	}

}

void Game::displayStalemate() {
	cout << "Stalemate!" << endl;
	window->drawString(10, 10, "Stalemate!");
	sleep(3000);
	window->fillRectangle(9, 9, 200, 10, XWindow::White);

}

void Game::displayWin(bool isWhite) {
	if (isWhite) {
		cout << "White wins!" << endl;
					window->drawString(10, 10, "White wins!");
		sleep(3000);
		window->fillRectangle(9, 9, 200, 10, XWindow::White);

	} else {

		cout << "Black wins!" << endl;
					window->drawString(10, 10, "Black wins!");
		sleep(3000);
		window->fillRectangle(9, 9, 200, 10, XWindow::White);
	}
}


void Game::displayOrigSetup() {

	window->drawString(72, 77, "r");
	window->drawString(122, 77, "n");
	window->drawString(172, 77, "b");
	window->drawString(222, 77, "q");
	window->drawString(272, 77, "k");
	window->drawString(322, 77, "b");
	window->drawString(372, 77, "n");
	window->drawString(422, 77, "r");

	for (int i = 1; i <= 8; ++i) {
		window->drawString(22 + (50 * i), 127, "p");
		window->drawString(22 + (50 * i), 377, "P");

	}
	
	window->drawString(72, 427, "R");
	window->drawString(122, 427, "N");
	window->drawString(172, 427, "B");
	window->drawString(222, 427, "Q");
	window->drawString(272, 427, "K");
	window->drawString(322, 427, "B");
	window->drawString(372, 427, "N");
	window->drawString(422, 427, "R");

}

////////////////////////////////////////////////////////////////////


// This program is the command interpreter for the chess game.

void Game::init() {
    XWindow w;
	*window = w;
    isRunning = true;
    mode = "menu";

	// draws the initial board
	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {
			if ((i + j) % 2) {
				window->fillRectangle(50 * i, 50 * j, 50, 50, XWindow::Cyan);
			}
			else {

				window->fillRectangle(50 * i, 50 * j, 50, 50, XWindow::White);
			}
		}
	}

	window->drawLine(50, 50, 450, 50);
	window->drawLine(50, 50, 50, 450);
	window->drawLine(450, 450, 450, 50);
	window->drawLine(450, 450, 50, 450);


	for (int i = 1; i <= 8; ++i) {
		string s{ 'a' + i - 1 };
		window->drawString(22 + (50 * i), 40, s);
	}

	for (int i = 1; i <= 8; ++i) {
		string s{ 'a' + i - 1 };
		window->drawString(22 + (50 * i), 470, s);
	}

	for (int i = 1; i <= 8; ++i) {
		string s{ i + '0' };
		window->drawString(35, 27 + (50 * (9 - i)), s);
		window->drawString(460, 27 + (50 * (9 - i)), s);
	}


}

// handles a single command at a time
// game, move, setup, or resign
void Game::handleEvents() {

	string line;
	// maybe just have input "quit" to end
    if(!getline(cin, line)) { 
		// crtl+D game is over
		isRunning = false;
		return;
	}
	stringstream linestream(line);
	string command;
    bool whitemoves = true;
    linestream >> command; // read a command

    if (mode == "menu") {
        if (command == "game") {
			string white;
			string black;
			int level;
			linestream >> white >> black;

			// check player types
			if (white == "human") {
				p1 = new Human{0};
			}
			else if (isComputer(white, level)) {
				if (level == 1) {
					p1 = new One{0, level};
				} else if (level == 2) {
					p1 = new Two{0,level};
				} else if (level == 3) {
					p1 = new Three{0,level};
				} else {
					p1 = new Four{0,level};
				}
			}
			else {
				cout << "ERROR: Invalid player type. Must be 'human' or 'computer[1-4]'" << endl;
				cout << "Please re-enter game start command." << endl;
				return;
			}

			if (black == "human") {
				p1 = new Human{1};
			}
			else if (isComputer(black, level)) {
				if (level == 1) {
					p1 = new One{1, level};
				} else if (level == 2) {
					p1 = new Two{1,level};
				} else if (level == 3) {
					p1 = new Three{1,level};
				} else {
					p1 = new Four{1,level};
				}
			}
			else {
				cout << "ERROR: Invalid player type. Must be 'human' or 'computer[1-4]'" << endl;
				cout << "Please re-enter game start command." << endl;
			}

			// begin the game...
			mode = "game";
			board = new twoPlayerBoard;
			board->origSetup(); // default setup
			score = new Score;
			cout << "Started new game!" << endl;
			return;


        } else if (command == "setup") {
            mode = "setup";
			return;
        } else {
			cout << "Unrecognized command. Please try again." << endl;
			return;
		}

	// assumes that game has started and board has been set up
    } else if (mode == "game") {
		if (command == "resign") {
			if (whitemoves) {
				cout << "Black wins!" << endl;
				score->blackWin();
			}
			else {
				cout << "White wins!" << endl;
				score->whiteWin();
			}
			mode = "menu";
		}
		else if (command == "move") {
			// if the command is "move"
			string from;
			string to;
			linestream >> from >> to;
			if (isValidPosition(from) && isValidPosition(to)) { // is valid positions
				// GAMEFLOW.txt PLAYER MOVE OCCURS
			}
			else {
				cout << "ERROR: invalid position/s." << endl;
			}
		} else if (command == "setup") {
			cout << "ERROR: setup can only be called before a game has started." << endl;
			return;
		} else {
			cout << "ERROR: Invalid game command." << endl;
			return;
		}
    } else if (mode == "setup") {
		cout << "Current Board Configuration:" << endl;
		board->printBoard();
		string black;

		if (command == "+") {
			string piece;
			string position;
			cin >> piece >> position;

			if (isValidPiece(piece)) {
				if (isValidPosition(position)) {
					board->insertP(piece, position);
					// do add thing here
				}

			}
			else {
				cout << "ERROR: Invalid. Must be [a-h][1-8] and piece r, n, b, q, k, p, R, N, B, Q, K, P" << endl;
			}
		}
		else if (command == "-") {
			string position;
			cin >> position;
			if (isValidPosition(position)) {
				board->removeP(position);
			}
			else {

				cout << "ERROR: Invalid position. Must be [a-h][1-8]" << endl;
			}
		}
		else if (command == "=") {

			string color;

			if (cin >> color);

			if (color == "white") {

				// white's turn to go next

			}
			else if (color == "black") {

				// black's turn to go next

			}
		}
		else if (command == "done") {
			// verify the board

			if (board->verify()) {

				// add thing here

					mode = "game"; // we are now in the game mode

			}
			else {
				cout << "ERROR: Setup conditions are not satisfied." << endl;

			}
		}
    }
}


// updates the graphics and text display
void Game::update() {



}


void Game::quit() {
	// print winning results
	if (score) {
		score->printScore();
	}
	cout << endl  << "Thanks for playing!" << endl;
	// delete and free stuff here
    delete window;
    delete board;
    delete score;
	delete p1;
	delete p2;
}

bool Game::running() {
    return isRunning;
}