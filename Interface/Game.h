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

class twoPlayerBoard; // game board
class XWindow;        // game graphic window
class Board;          // abstract board
class Score;          // score
class Player;         // player
class Game
{
    std::unique_ptr<XWindow> window;            // graphic window
    std::unique_ptr<Board> board;               // abstract board
    std::unique_ptr<Score> score;               // score
    bool isRunning;                             // boolean to check if the game is running
    std::string mode;                           // the modes of the game (game, setup, menu)
    std::unique_ptr<Player> p1;                 // white player
    std::unique_ptr<Player> p2;                 // black player
    bool whitemoves;                            // true if it is white's turn
    std::vector<std::unique_ptr<Move>> history; // game move history
    void printBoard();                          // outputs the board
    // resets the board to start a new game
    // occurs after resign, checkmate, stalemate
    void reset();
    void fill(int x, int y);                         // fills the graphic board at coordinate (x, y) with a blank tile (erases the piece)
    void drawPiece(std::string piece, int x, int y); // draws a piece at coordinate (x, y) with piece string
    // setup: inserts a piece at given position
    // assumes that piece and position are valid
    void insertNewPiece(std::string validpiece, std::string position);
    // draws blank square over position
    void removePiece(std::string position);
    // display the original board on the graphic window; if reset, then clear out middle slots
    void displayOrigSetup(bool reset);
    // display that king is in check on the graphic window (isWhite -> white king and vice versa)
    void displayCheck(bool isWhite);
    // display a stalemate on the graphic window
    void displayStalemate();
    // display a win on the graphic window (isWhite -> white and vice versa)
    void displayWin(bool isWhite);
    // update status of all pieces, return movability
    int updateSt();

public:
    Game();          // constructor
    virtual ~Game(); // destructor
    void init();     // initializes a board on the graphics window as well as its pieces and sets up the board
    // handles a single command at a time
    // game, move, setup, or resign
    void handleEvents();
    void update();       // updates the graphics and text display
    void quit();         // quits the game and deallocates memory
    bool running();      // returns true if game is running
    void resetRecents(); // resets the recency of the pieces
};

#endif