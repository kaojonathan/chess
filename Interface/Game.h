#ifndef GAME_H_
#define GAME_H_


#include <X11/Xlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;



class XWindow;
class Board;
class Score;

class Game {


    XWindow *window;
    Board *board;
    Score *score;
    bool isRunning;

    string mode; // game, setup, menu, etc.






    public:



    Game();
    ~Game();
    void init(); // starts a game window
    void handleEvents();
    void update();
    void render();
    void quit(); // quits the game and deallocates memory
    bool running();





};

#endif