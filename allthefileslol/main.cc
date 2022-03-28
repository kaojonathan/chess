#include "board.h"
#include "twoPlayerBoard.h"
#include "score.h"
#include <iostream>
#include <sstream>
#include <string>
#include "window.h"
#include "Game.h"

using namespace std;

Game *game = nullptr;

int main(int argc, const char * argv[]) { // implemented using help from https://www.youtube.com/watch?v=44tO977slsU (type "game loop" and do some research)
	Window w;
	game = new Game{&w};

	game->init(); // initialize the game

	while (game->running()) { // the game loop

		game->handleEvents(); // handle input commands
		game->update(); // update the model??????

	}

	game->quit();

	return 0;
	// handle any user input
	// update all objects
	// render changes to the display

}
