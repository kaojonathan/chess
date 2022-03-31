#ifndef GAME_H_
#define GAME_H_

#include <X11/Xlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


class XWindow;
class Board;
class Score;
class Player;

class Game {
    XWindow *window;
    Board *board;
    Score *score;
    bool isRunning;
    std::string mode; // game, setup, menu, etc.
    Player *p1; // white
    Player *p2; // black
    bool whitemoves; // true if it is white's turn
    int tracked; // tracks number of moves reflected on the window
    std::vector<std::string> history; 

    void printBoard();
    void reset();
    void fill(int x, int y);
    void drawPiece(std::string piece, int x, int y);
    void insertNewPiece(std::string validpiece, std::string position);
    void removePiece(std::string position);

    void displayOrigSetup();
    void displayCheck(bool isWhite);
    void displayStalemate();
    void displayWin(bool isWhite);

    public:
        Game();
        ~Game();
        void init(); // starts a game window
        void handleEvents();
        void update();
        void quit(); // quits the game and deallocates memory
        bool running();

};

#endif