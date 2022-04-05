#include "Interface/Game.h"
#include <stdexcept>
using namespace std;

// "game loop" idea inspired by https://www.youtube.com/watch?v=44tO977slsU
int main(int argc, const char *argv[])
{
	Game game;
	game.init(); // initialize the game
	while (game.running())
	{
		try
		{
			// handle input commands
			game.handleEvents();
			// update the the graphic model and text model
			game.update();
		}
		catch (runtime_error &e)
		{ // catch invalid input
			cout << e.what() << endl;
		}
	}
	game.quit(); 
	return 0;
}
