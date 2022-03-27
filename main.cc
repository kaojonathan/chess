#include "board.h"
#include "twoPlayerBoard.h"
#include "score.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// This program is the command interpreter for the chess game.


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
		if ((a <= position[0] <= h) && (1 <= position[1] <= 8)) {
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




int main() {

	Score score;
	string line;

	while (getline(cin, line)) // reads each line (command followed by parameter values)
	{
		char c;
		string name;
		string number;
		int i;
		twoPlayerBoard board;

		stringstream linestream(line);

		string command;

		linestream >> command;


		if (command == "game")
		{ // if the command is "game"

			cout << "Started new game!" << endl;

			bool whitemoves = true;
			string white;
			string black;
			int difficulty;
			linestream >> white >> black;

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
				continue;
			}

			while (getline(cin, line)) // reads each line (we are now in the game loop)
			{
				stringstream gamestream(line);
				gamestream >> command;

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
					break; // break
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
			}


			/*
			*
			* game white-player black-player starts a new game. The parameters white-player and black-player
			*    can be either human or computer[1-4].
			*/
		}
		else if (command == "resign")
		{ // if the command is "resign"
			cout << "ERROR: resign can only be called after a game has started." << endl;
		}
		else if (command == "move")
		{ // if the command is "move"

			cout << "ERROR: move can only be called after a game has started." << endl;

		}
		else if (command == "setup")
		{ // if the command is "setup"


		

			while (getline(cin, line)) // reads each line (we are now in the game loop)
			{

				cout << "Current Board Configuration:" << endl;
				board.print();
				stringstream setupstream(line);

				string language;

				string black;
				int difficulty;
				setupstream >> language;

				if (language == "+") {

					string piece;
					string position;
					setupstream >> piece >> position;

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
				else if (language == "-") {
					string position;
					setupstream >> position;
					if (isValidPosition(position)) {
						board.removePiece(position);
					}
					else {

						cout << "ERROR: Invalid position. Must be [a-h][1-8]" << endl;
					}
				}
				else if (language == "=") {

					string color;

					setupstream >> color;

					if (color == "white") {

						// white's turn to go next

					}
					else if (color == "black") {

						// black's turn to go next

					}
				}
				else if (language == "done") {
					// verify the board

					if (board.verifySetup()) {

						// add thing here
						break;
					}
					else {
						cout << "ERROR: Setup conditions are not satisfied." << endl;

					}
				}
			}

			/////////////////////// GAME THAT STARTS AFTER SETUP ////////////////////////

			bool whitemoves = true;

			while (getline(cin, line)) // reads each line (we are now in the game loop)
			{
				stringstream gamestream(line);
				gamestream >> command;

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
					break; // break
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
				}
				else if (command == "setup") {
					cout << "ERROR: setup can only be called before a game has started." << endl;
				}
				else {
					cout << "ERROR: Invalid game command." << endl;
				}
			}
			///////////////////////////////////////////////////////////////////////////////
		}
		else {
			cout << "ERROR: Invalid command." << endl;
		}
	}

	// print winning results
	score.printScore();
	cout << endl  << "Thanks for playing!" << endl;
	// delete and free stuff here

}
