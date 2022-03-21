#include "board.h"
#include "score.h"
#include <iostream>

using namespace std;


// isHuman checks if the 'player' is a "human"
bool isHuman(string player)
{
	if (player == "human")
	{
		return true;
	}
	else
	{
		return false;
	}
}

// isComputer checks if the 'player' is a "computer". if it is, also updates level to give the difficulty of the computer
bool isComputer(string player, int& level)
{
	if (player.substr(0, 8) == "computer")
	{
		if ((player[8] = '[') && (player[10] = ']')) {
			if ('1' <= player[9] <= 4) {
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

bool isValidMove(string from, string to) {


	// can't implement right now



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

bool isValidPiece(string piece) {
	if (piece.length() == 1) {
		if ((piece[0] == "r") || (piece[0] == "n") || (piece[0] == "b") || (piece[0] == "q") || (piece[0] == "k") || (piece[0] == "p")
			|| (piece[0] == "R") || (piece[0] == "N") || (piece[0] == "B") || (piece[0] == "Q") || (piece[0] == "K") || (piece[0] == "P")) {
			return true;
		}
	}
	else {
		return false;
	}
}

// hi


int main() {

	Score score;




	std::string line;



	while (getline(std::cin, line)) // reads each line (command followed by parameter values)
	{
		char c;
		std::string name;
		std::string number;
		int i;









		std::stringstream linestream(line);

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
				cout << "Invalid player type. Must be 'human' or 'computer[1-4]'" << endl;
				continue;
			}

			while (getline(std::cin, line)) // reads each line (we are now in the game loop)
			{
				std::stringstream gamestream(line);
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
					cout << "setup can only be called before a game has started." << endl;
				}
				else {
					cout << "Invalid game command." << endl;
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
			cout << "resign can only be called after a game has started." << endl;
		}
		else if (command == "move")
		{ // if the command is "move"

			cout << "move can only be called after a game has started." << endl;

		}
		else if (command == "setup")
		{ // if the command is "setup"

			string language;

			string black;
			int difficulty;
			linestream >> language;

			if (language == "+") {

				string piece;
				string position;
				linestream >> piece >> position;

				if (isValidPiece(piece)) {
					if (isValidPosition(position)) {

						// do add thing here


					}

				} else {

					cout << "Invalid. Must be [a-h][1-8] and piece r, n, b, q, k, p, R, N, B, Q, K, P" << endl;

				}



			}
			else if (language == "-") {
				string position;
				linestream >> position;
				if (isValidPosition(position)) {

					// do thing here


				}
				else {


					cout << "Invalid position. Must be [a-h][1-8]" << endl;

				}



			}
			else if (language == "=") {

				string color;

				linestream >> color;

				if (color == "white") {

					// white's turn to go next



				}
				else if (color == "black") {

					// black's turn to go next


				}




			}
			else if (language == "done") {


				// verify the board



			}



			// setup(...)



			/*


			 setup enters setup mode, within which you can set up your own initial board configurations. This can only be done
when a game is not currently running. Within setup mode, the following language is used:
� + K e1 places the piece K (i.e., white king in this case) on the square e1. If a piece is already on that square, it
is replaced. The board should be redisplayed.
� - e1 removes the piece from the square e1 and then redisplays the board. If there is no piece at that square, take
no action.
� = colour makes it colour�s turn to go next.
� done leaves setup mode.

Upon completion of setup mode, you must verify that the board contains exactly one white king and exactly one black
king; that no pawns are on the first or last row of the board; and that neither king is in check. The user cannot leave
setup mode until these conditions are satisfied. We recommend doing setup mode early, as it may facilitate testing.
You are not required to handle the question of whether a player has the right to castle or make an en passant capture
after board setup. You are free to simply assume that these are not valid options, or if you choose, you can find a way to
incorporate them into the setup phase

			*/




		}
		else {
			cout << "Invalid command." << endl;
		}
	}

	// print winning results
	score.printScore();
	cout << endl  << "Thanks for playing!" << endl;
	// delete and free stuff here



}

/*
Board Display can look like this

8 rnbqkbnr
7 pppppppp
6 _ _ _ _
5 _ _ _ _
4 _ _ _ _
3 _ _ _ _
2 PPPPPPPP
1 RNBQKBNR

  abcdefgh


*/