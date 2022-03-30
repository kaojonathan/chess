#include <iostream>
#include "Interface/Game.h"

using namespace std;


// implemented using help from https://www.youtube.com/watch?v=44tO977slsU 
// (type "game loop" and do some research)
int main(int argc, const char * argv[]) { 

	Game *game = new Game;

	game->init(); // initialize the game

	while (game->running()) { // the game loop
		// handle input commands
		game->handleEvents(); 
		// update the the graphic model and text model
		game->update(); // maybe have this have parameter move to minimize graphic load
	}

	game->quit();

	return 0;


}
