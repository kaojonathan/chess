#include "Interface/Game.h"
#include "undo.h"
#include <stdexcept>
using namespace std;


// implemented using help from https://www.youtube.com/watch?v=44tO977slsU 
// (type "game loop" and do some research)
int main(int argc, const char * argv[]) { 

	Game game;

	game.init(); // initialize the game

	while (game.running()) { // the game loop
		try {
			// handle input commands
			game.handleEvents(); 
			// update the the graphic model and text model
			game.update(); 
		} catch (runtime_error &e) {
			cout << e.what() << endl;
		} catch (Undo &e) {
			cout << e.what() << endl;



		}

	}

	game.quit();
	return 0;


}
