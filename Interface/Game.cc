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


Game::Game() : window{new XWindow}, 
			   board{new twoPlayerBoard},
			   score{new Score},
			   isRunning{true} {
    mode = "menu";
	whitemoves = true;
}

Game::~Game() {
	delete window;
	delete board;
	delete score;
	delete p1;
	delete p2;
}

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

// checks if given position is in bounds (ex. e4)
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

// used for set up to check if a piece symbol is valid
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
// assumes that piece and position are valid
void Game::insertNewPiece(std::string validpiece, std::string position) {
	int col = position[0] - 'a';
	int row = 8 - (position[1] - '0');
	// if old piece drawn there
	if (board->getPiece(col, row)) fill(col, row);
	drawPiece(validpiece, col, row);
}

// draws blank square over position
void Game::removePiece(std::string position) {
	// clears out square if a piece exists 
	// !!!!! MAY NOT WORK IF PIECE HAS ALREADY BEEN DELETED?!!!
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


// updates the graphics and text display
void Game::update() {
	// display text
	board->printBoard();
	// update window grphics here...


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
    linestream >> command; // read a command

	// initial mode
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
				// reset p1
				delete p1;
				return;
			}

			// begin the game
			mode = "game";
			board->origSetup(); // default setup
			cout << "Started new game!" << endl;
			return;


        } else if (command == "setup") {
            mode = "setup";
			cout << "Entered set up mode..." << endl;
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
		this->update();

		if (command == "+") {
			string piece;
			string position;
			if (cin >> piece >> position);

			if (isValidPiece(piece) && isValidPosition(position)) {
				board->insertP(piece, position);
				insertNewPiece(piece, position);
				cout << "Inserted piece at: " << position;
			}
			else {
				cout << "ERROR: Invalid. Must be [a-h][1-8] and ";
				cout << "piece r, n, b, q, k, p, R, N, B, Q, K, P" << endl;
			}
			return;
		}
		else if (command == "-") {
			string position;
			if (cin >> position);
			if (isValidPosition(position)) {
				removePiece(position);
				board->removeP(position);
				cout << "Removed piece at: " << position;
			}
			else {
				cout << "ERROR: Invalid position. Must be [a-h][1-8]" << endl;
			}
			return;
		}
		else if (command == "=") {
			string color;
			if (cin >> color);
			if (color == "white") {
				whitemoves = true;
			}
			else if (color == "black") {
				whitemoves = false;
			} else {
				cout << "Invalid color, please try again." << endl;
			}
			return;
		}
		else if (command == "done") {
			// verify the board
			if (board->verify()) {
					mode = "game"; // we are now in the game mode
					cout << "Game-setup Complete!" << endl;
			}
			else {
				cout << "ERROR: Setup conditions are not satisfied." << endl;
				cout << "Please continue set-up" << endl;
			}
			return;
		} else {
			cout << "Unrecognized setup command." << endl;
			return;
		}
    }
}



void Game::quit() {
	// print winning results
	if (score) {
		score->printScore();
	}
	cout << endl  << "Thanks for playing!" << endl;
}

bool Game::running() {
    return isRunning;
}