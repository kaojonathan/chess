#ifndef GAME_H_
#define GAME_H_

#include <X11/Xlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "../Pieces/Move/move.h"


class twoPlayerBoard;
class XWindow;
class Board;
class Score;
class Player;

class Game {
    std::unique_ptr<XWindow> window;
    std::unique_ptr<Board> board;
    std::unique_ptr<Score> score;
    bool isRunning;
    std::string mode; // game, setup, menu, etc.
    std::unique_ptr<Player> p1; // white
    std::unique_ptr<Player> p2; // black
    bool whitemoves; // true if it is white's turn
    std::vector<std::unique_ptr<Move>> history; // change to vector<Move *>

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