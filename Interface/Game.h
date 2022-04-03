#ifndef GAME_H_
#define GAME_H_

#include <X11/Xlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../PiecesAndBoard/Move/move.h"


class twoPlayerBoard;
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
    std::vector<Move *> history; // change to vector<Move *>

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
        virtual ~Game();
        void init(); // starts a game window
        void handleEvents();
        void update();
        void quit(); // quits the game and deallocates memory
        bool running();
        void resetRecents();

};

#endif