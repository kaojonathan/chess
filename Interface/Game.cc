#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <stdexcept>
#include "../Graphics/XWindowImpl.h"
#include "Game.h"
#include "../Graphics/window.h"
#include "../PiecesAndBoard/board.h"
#include "../PiecesAndBoard/twoPlayerBoard.h"
#include "../Players/one.h"
#include "../Players/two.h"
#include "../Players/three.h"
#include "../Players/four.h"
#include "../score.h"
#include "../Players/human.h"
#include "../Players/computer.h"
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



// returns the level of the computer, otherwise returns 0
int isComputer(string player)
{
	if (player.substr(0, 8) == "computer")
	{
		if ((player[8] = '[') && (player[10] = ']')) {
			if ('1' <= player[9] && player[9] <= 4) {
				return player[9];	
			}
		}
	}
	else
	{
		return 0;
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
void Game::drawPiece(std::string piece, int x, int y) {
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
	fill(position[0] - 'a', 8 - (position[1] - '0'));
}

// prints the board
void Game::printBoard()
{
	for (int i = 0; i < 8; ++i)
	{
		cout << 8 - i << ' ';
		for (int j = 0; j < 8; ++j)
		{
			if (board[i][j] == nullptr)
			{ // empty tile
				if ((i + j) % 2)
				{ // if sum is odd it's a white tile
					cout << '_';
				}
				else
				{ // otherwise it's a black tile

					cout << ' ';
				}
			}
			else
			{ // piece is on it
				cout << board[i][j]->getRep();
			}
		}
		cout << endl;
	}
	cout << endl
		 << "  ";
	for (int i = 0; i < 8; ++i)
	{

		char s = 'a' + i;
		cout << s;
	}
	cout << endl;
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

// draws the initial board
void Game::init() {	
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

	// set up the actual board with default pieces
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	board->origSetup();
}




// updates the graphics and text display
void Game::update() {
	// display text
	printBoard();
	// update window grphics here...
	int totalMoves = history.size();
	while (tracked < totalMoves) {
		// update board using history[tracked]
		// this way entire board doesnt get redrawn

		
		++tracked;
	}
}

// resets the board to start a new game
// occurs after resign, checkmate, stalemate
void Game::reset() {
	// board reset, please enter setup or start a new game
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
			linestream >> white >> black;	
			
			// check player types
			int whiteLevel = isComputer(white);
			int blackLevel = isComputer(black);

			if (white == "human" || whiteLevel) && 
				(black == "human" || blackLevel) {
					if (white == "human") {
						p1 = new Human{0};
					} else {
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
					if (black == "human") {
						p2 = new Human{1};
					} else {
						if (level == 1) {
							p2 = new One{1, level};
						} else if (level == 2) {
							p2 = new Two{1,level};
						} else if (level == 3) {
							p2 = new Three{1,level};
						} else {
							p2 = new Four{1,level};
						}
					}
			} else {
				throw runtime_error{"Invalid player type. Must be 'human' or 'computer[1-4]'\n" +
									 "Please re-enter game start command."};
			}

			// begin the game
			mode = "game";

			p1->claimPieces();
			p2->claimPieces();
			cout << "Started new game!" << endl;
			return;


        } else if (command == "setup") {
            mode = "setup";
			cout << "Entered set up mode..." << endl;
			return;
        } else {
			throw runtime_error{"Unrecognized command. Please try again."};
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
			// reset game?
			mode = "menu";
		}
		else if (command == "move") {
			// if the command is "move"
			int end;
			p1->unsetStatus();
			p2->unsetStatus();
			if (whitemoves) {
				end = p1->checkStatus();
				p2->checkStatus();
			} else {
				end = p2->checkStatus();
				p1->checkStatus();
			}
			if (end == 1) {
				// the player that is about to move
				// is checkmated
				if (whitemoves) {
					score->blackWin();
				} else {
					score->whiteWin();
				}
				//reset
			} else if (end ==2) {
				// stalemate
				score->tie();
				//reset
			} else { // moves available
				if (whitemoves) {
					if (p1->getType() == 0) {
						// human
						string from;
						string to;
						linestream >> from >> to;
						if (isValidPosition(from) && isValidPosition(to)) { 
							int status = p1->move(from[0], from[1], to[0], to[1]);
							if (status == 0) {
								throw runtime_error{"Illegal move attempted. Please try another."};
							}
						} else {
							throw runtime_error{"Unrecognized move. Please re-enter."};
						}
					} else {
						// computer
						p1->move(0,0,0,0);
						return;
					}
				} else { // black's turn
					if (p2->getType() == 0) {
						// human
						string from;
						string to;
						linestream >> from >> to;
						if (isValidPosition(from) && isValidPosition(to)) { 
							int status = p2->move(from[0], from[1], to[0], to[1]);
							if (status == 0) {
								throw runtime_error{"Illegal move attempted. Please try another."};
							}
						} else {
							throw runtime_error{"Unrecognized move. Please re-enter."};
						}
					} else {
						// computer
						p2->move(0,0,0,0);
						return;
					}
				}
			}
		} else if (command == "setup") {
			throw runtime_error{"ERROR: setup can only be called before a game has started."};
		} else {
			throw runtime_error{"ERROR: Invalid game command."};
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
				return;
			}
			else {
				throw runtime_error{"ERROR: Invalid. Must be [a-h][1-8] and " +
									"piece r, n, b, q, k, p, R, N, B, Q, K, P"};
			}
		}
		else if (command == "-") {
			string position;
			if (cin >> position);
			if (isValidPosition(position)) {
				removePiece(position);
				board->removeP(position);
				cout << "Removed piece at: " << position;
				return;
			}
			else {
				throw runtime_error{"ERROR: Invalid position. Must be [a-h][1-8]"};
			}
		}
		else if (command == "=") {
			string color;
			if (cin >> color);
			if (color == "white") {
				whitemoves = true;
				return;
			}
			else if (color == "black") {
				whitemoves = false;
				return;
			} else {
				throw runtime_error{"Invalid color, please try again."};
			}
		}
		else if (command == "done") {
			// verify the board
			if (board->verify()) {
					mode = "menu"; 
					cout << "Game-setup Complete!" << endl;
					return;
			}
			else {
				throw runtime_error{"ERROR: Setup conditions are not satisfied.\n" +
									"Please continue set-up"};
			}
			
		} else {
			throw runtime_error{"Unrecognized Command."};
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