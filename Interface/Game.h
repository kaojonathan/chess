#ifndef GAME_H_
#define GAME_H_

#include <X11/Xlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>


class XWindow;
class Board;
class Score;

class Game {
    XWindow *window;
    Board *board;
    Score *score;
    bool isRunning;
    std::string mode; // game, setup, menu, etc.
    Player *p1; // white
    Player *p2; // black
    bool whitemoves; // true if it is white's turn

    public:
        Game();
        ~Game();
        void init(); // starts a game window
        void handleEvents();
        void update();
        void quit(); // quits the game and deallocates memory

        void fill(int x, int y);
        void drawPiece(string piece, int x, int y);
        void insertNewPiece(std::string validpiece, std::string position);
        void removePiece(std::string position);

        void displayOrigSetup();
        
        void displayCheck(bool isWhite);
        void displayStalemate();
        void displayWin(bool isWhite);
        bool running();
};

#endif