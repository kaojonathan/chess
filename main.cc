#include "Interface/Game.h"

using namespace std;


// implemented using help from https://www.youtube.com/watch?v=44tO977slsU 
// (type "game loop" and do some research)
int main(int argc, const char * argv[]) { 

	Game *game = new Game;

	game->init(); // initialize the game

	while (game->running()) { // the game loop

		try {
			// handle input commands
			game->handleEvents(); 
			// update the the graphic model and text model
			game->update(); 
		} catch (...) {
			// fill in with runtime error
		}

	}

	game->quit();
	delete game;
	return 0;


}
