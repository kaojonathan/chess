#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"
#include "XWindowImpl.h"
#include "Game.h"
#include "window.h"
using namespace std;


Game::Game() {}

Game::~Game() {}



/////////// HELPER FUNCTIONS /////////////////


// isHuman checks if the 'player' is a "human"
bool isHuman(string player)
{
	return (player == "human");
}

// isComputer checks if the 'player' is a "computer". if it is, also updates level to give the difficulty of the computer
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


////////////////////////////////////////////////////////////////////


// This program is the command interpreter for the chess game.

void Game::init() {
    XWindow w;
	*window = w;
    isRunning = true;
    mode = "menu";


	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {

			if ((i + j) % 2) {
				w.fillRectangle(50 * i, 50 * j, 50, 50, XWindow::Cyan);
			}
			else {

				w.fillRectangle(50 * i, 50 * j, 50, 50, XWindow::White);

			}

		}




	}

	w.drawLine(50, 50, 450, 50);
	w.drawLine(50, 50, 50, 450);
	w.drawLine(450, 450, 450, 50);
	w.drawLine(450, 450, 50, 450);



	w.drawString(72, 77, "r");
	w.drawString(122, 77, "n");
	w.drawString(172, 77, "b");
	w.drawString(222, 77, "q");
	w.drawString(272, 77, "k");
	w.drawString(322, 77, "b");
	w.drawString(372, 77, "n");
	w.drawString(422, 77, "r");

	for (int i = 1; i <= 8; ++i) {
		w.drawString(22 + (50 * i), 127, "p");
		string s{ 'a' + i - 1 };
		w.drawString(22 + (50 * i), 40, s);
	}

	for (int i = 1; i <= 8; ++i) {
		w.drawString(22 + (50 * i), 377, "P");
		string s{ 'a' + i - 1 };
		w.drawString(22 + (50 * i), 470, s);
	}

	for (int i = 1; i <= 8; ++i) {
		string s{ i + '0' };
		w.drawString(35, 27 + (50 * (9 - i)), s);
		w.drawString(460, 27 + (50 * (9 - i)), s);
	}


	w.drawString(72, 427, "R");
	w.drawString(122, 427, "N");
	w.drawString(172, 427, "B");
	w.drawString(222, 427, "Q");
	w.drawString(272, 427, "K");
	w.drawString(322, 427, "B");
	w.drawString(372, 427, "N");
	w.drawString(422, 427, "R");


}










void Game::handleEvents() {


	string line;
    getline(cin, line);
	stringstream linestream(line);
	string command;
    bool whitemoves = true;
    linestream >> command; // read a command


    if (mode == "menu") {

        if (command == "game") {


			string white;
			string black;
			int difficulty;
			linestream >> white >> black;

            bool correctinput = true;
			if (isHuman(white)) {
				// do human thing
				// new Human(...)

                


			}
			else if (isComputer(white, difficulty)) {
				// do computer thing
				// new Computer(...)


			}
			else {
				cout << "ERROR: Invalid player type. Must be 'human' or 'computer[1-4]'" << endl;
				correctinput = false;
			}



			if (isHuman(black)) {


				// do human thing
				// new Human(...)

                


			}
			else if (isComputer(black, difficulty)) {


				// do computer thing
				// new Computer(...)


			}
			else {
				cout << "ERROR: Invalid player type. Must be 'human' or 'computer[1-4]'" << endl;
				correctinput = false;
			}

    
            if (correctinput) {

                
        mode = "game";
        board = new Board;
        score = new Score;
		cout << "Started new game!" << endl;

        // find a way to update the graphics as well?


            }





        } else if (command == "setup") {


            mode = "setup";



        }

    






    } else if (mode == "game") {

				if (command == "resign") {

					 // if the command is "resign"
					// resign(...)

						/*
						*
						*  resign concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a
						*   game.
						*
						*/

					if (whitemoves) {
						cout << "Black wins!" << endl;
						score.blackWin();

					}
					else {
						cout << "White wins!" << endl;
						score.whiteWin();
					}
					mode = "menu";
				}
				else if (command == "move") {
					// if the command is "move"
					string from;
					string to;
					linestream >> from >> to;


					if (isValidPosition(from) && isValidPosition(to)) { // is valid positions

						// do add thing here

					}
					else {
						cout << "ERROR: invalid position/s." << endl;

					}


					// move(...)

		/*

		* A move consists of the command move, followed by the starting and ending coordinates of the piece to be moved. For
		* example: move e2 e4. Castling would specified by the two-square move for the king: move e1 g1 or move e1
		* c1 for white. Pawn promotion would additionally specify the piece type to which the pawn is promoted: move e7
		* e8 Q. In the case of a computer player, the command move (without arguments) makes the computer player make a
		* move.

		*/

				}
				else if (command == "setup") {
					cout << "ERROR: setup can only be called before a game has started." << endl;
				}
				else {
					cout << "ERROR: Invalid game command." << endl;
				}




    } else if (mode == "setup") {


				cout << "Current Board Configuration:" << endl;

				board.print();


				string black;
				int difficulty;

				if (command == "+") {

					string piece;
					string position;
					command >> piece >> position;

					if (isValidPiece(piece)) {
						if (isValidPosition(position)) {

							board.insertNewPiece(piece, position);

							// do add thing here

						}

					}
					else {

						cout << "ERROR: Invalid. Must be [a-h][1-8] and piece r, n, b, q, k, p, R, N, B, Q, K, P" << endl;
					}
				}
				else if (command == "-") {
					string position;
					command >> position;
					if (isValidPosition(position)) {
						board.removePiece(position);
					}
					else {

						cout << "ERROR: Invalid position. Must be [a-h][1-8]" << endl;
					}
				}
				else if (command == "=") {

					string color;

					command >> color;

					if (color == "white") {

						// white's turn to go next

					}
					else if (color == "black") {

						// black's turn to go next

					}
				}
				else if (command == "done") {
					// verify the board

					if (board.verifySetup()) {

						// add thing here

						 mode = "game"; // we are now in the game mode

					}
					else {
						cout << "ERROR: Setup conditions are not satisfied." << endl;

					}
				}





    }






}

void Game::update() {



}

void Game::render() {




}

void Game::quit() {


	// print winning results
	score->printScore();
	cout << endl  << "Thanks for playing!" << endl;
	// delete and free stuff here


    delete window;
    delete board;
    delete score;


}

void Game::running() {

    return isRunning;

}
