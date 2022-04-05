#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <stdexcept>
#include <memory>
#include "../Graphics/XWindowImpl.h"
#include "Game.h"
#include "../Pieces/Move/move.h"
#include "../Pieces/Move/normal.h"
#include "../Pieces/Move/capture.h"
#include "../Pieces/Move/castle.h"
#include "../Pieces/Move/enpassant.h"
#include "../Pieces/Move/promotion.h"
#include "../Pieces/Move/promotioncap.h"
#include "../Graphics/window.h"
#include "../Board/board.h"
#include "../Board/twoPlayerBoard.h"
#include "../Pieces/king.h"
#include "../Pieces/queen.h"
#include "../Pieces/rook.h"
#include "../Pieces/knight.h"
#include "../Pieces/bishop.h"
#include "../Pieces/pawn.h"
#include "../Players/one.h"
#include "../Players/two.h"
#include "../Players/three.h"
#include "score.h"
#include "../Players/human.h"
#include "../Players/computer.h"
using namespace std;

// constructor, initializes a new XWindow, twoPlayerBoard, Score, and isRunning = true
Game::Game() : window{unique_ptr<XWindow>{new XWindow}},
			   board{unique_ptr<twoPlayerBoard>{new twoPlayerBoard}},
			   score{unique_ptr<Score>{new Score}},
			   isRunning{true}
{ // default menu mode and white moves first
	mode = "menu";
	whitemoves = true;
}

// destructor
Game::~Game() {}

/////////// HELPER FUNCTIONS /////////////////

// returns the level of the computer, otherwise returns 0
int isComputer(string player)
{
	if (player.substr(0, 8) == "computer")
	{
		if ((player[8] = '[') && (player[10] = ']'))
		{
			if ('1' <= player[9] && player[9] <= '4')
			{
				return player[9] - '0';
			}
		}
	}
	return 0;
}

// checks if given position is in bounds of the board (ex. e4)
bool isValidPosition(string position)
{
	if (position.length() == 2)
	{
		if (('a' <= position[0] && position[0] <= 'h') && (1 <= position[1] && position[1] <= 8))
		{
			return false;
		}
	}
	return true;
}

// used for set up to check if a piece symbol is valid
bool isValidPiece(string piece)
{
	if (piece.length() == 1)
	{
		return ((piece[0] == 'r') || (piece[0] == 'n') || (piece[0] == 'b') ||
				(piece[0] == 'q') || (piece[0] == 'k') || (piece[0] == 'p') ||
				(piece[0] == 'R') || (piece[0] == 'N') || (piece[0] == 'B') ||
				(piece[0] == 'Q') || (piece[0] == 'K') || (piece[0] == 'P'));
	}
	return false;
}

// fills the graphic board at coordinate (x, y) with a blank tile (erases the piece)
void Game::fill(int x, int y)
{
	// retain the checkerboard pattern
	if ((x + y + 2) % 2)
	{
		window->fillRectangle(50 * (x + 1), 50 * (y + 1), 50, 50, XWindow::Cyan);
	}
	else
	{
		window->fillRectangle(50 * (x + 1), 50 * (y + 1), 50, 50, XWindow::White);
	}
	// draw the borders of the board
	window->drawLine(50, 50, 450, 50);
	window->drawLine(50, 50, 50, 450);
	window->drawLine(450, 450, 450, 50);
	window->drawLine(450, 450, 50, 450);
}

// draws a piece at coordinate (x, y) with piece string
void Game::drawPiece(std::string piece, int x, int y)
{
	// retain the checkerboard pattern
	if ((x + y + 2) % 2)
	{
		window->fillRectangle(50 * (x + 1), 50 * (y + 1), 50, 50, XWindow::Cyan);
	}
	else
	{
		window->fillRectangle(50 * (x + 1), 50 * (y + 1), 50, 50, XWindow::White);
	}
	// draw the borders of the board
	window->drawLine(50, 50, 450, 50);
	window->drawLine(50, 50, 50, 450);
	window->drawLine(450, 450, 450, 50);
	window->drawLine(450, 450, 50, 450);
	// draw the piece
	window->drawString(25 + (50 * (x + 1)), 25 + (50 * (y + 1)), piece);
}

// setup: inserts a piece at given position
// assumes that piece and position are valid
void Game::insertNewPiece(std::string validpiece, std::string position)
{
	int col = position[0] - 'a';
	int row = 8 - (position[1] - '0');
	// if old piece drawn there clear it then draw the piece
	if (board->getPiece(col, row))
		fill(col, row);
	drawPiece(validpiece, col, row);
}

// draws blank square over position
void Game::removePiece(std::string position)
{
	// clears out square if a piece exists
	fill(position[0] - 'a', 8 - (position[1] - '0'));
}

// outputs the board
void Game::printBoard()
{
	for (int i = 0; i < 8; ++i)
	{
		cout << 8 - i << ' '; // the row numbers
		for (int j = 0; j < 8; ++j)
		{
			if (board->getPiece(j, i) == nullptr)
			{ // empty tile
				// retain checkerboard pattern
				if ((i + j) % 2)
				{ // if sum is odd it's a white tile
					cout << '_';
				}
				else
				{ // otherwise it's a black tile
					cout << ' ';
				}
			}
			else
			{ // piece is on it; output the piece!
				cout << board->getPiece(j, i)->getRep();
			}
		}
		cout << endl;
	}
	cout << endl
		 << "  ";
	for (int i = 0; i < 8; ++i)
	{
		char s = 'a' + i;
		cout << s; // the column numbers
	}
	cout << endl;
}

// display that king is in check on the graphic window (isWhite -> white king and vice versa)
void Game::displayCheck(bool isWhite)
{
	if (isWhite)
	{													  // if white King is in check
		cout << "White is in check." << endl;			  // output
		window->drawString(10, 10, "White is in check."); // show on graphic
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		window->fillRectangle(-5, -5, 200, 30, XWindow::White); // erase it after 3 secs
	}
	else
	{													  // if black King is in check
		cout << "Black is in check." << endl;			  // output
		window->drawString(10, 10, "Black is in check."); // show on graphic
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		window->fillRectangle(-5, -5, 200, 30, XWindow::White); // erase it after 3 secs
	}
}

// display a stalemate on the graphic window
void Game::displayStalemate()
{
	cout << "Stalemate!" << endl;			  // output
	window->drawString(10, 10, "Stalemate!"); // show on graphic
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	window->fillRectangle(-5, -5, 200, 30, XWindow::White); // erase it after 3 secs
}

// display a win on the graphic window (isWhite -> white and vice versa)
void Game::displayWin(bool isWhite)
{
	if (isWhite)
	{											   // if white King is in check
		cout << "White wins!" << endl;			   // output
		window->drawString(10, 10, "White wins!"); // show on graphic
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		window->fillRectangle(-5, -5, 200, 30, XWindow::White); // erase it after 3 secs
	}
	else
	{ // if black King is in check
		cout << "Black wins!" << endl;
		window->drawString(10, 10, "Black wins!"); // show on graphic
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		window->fillRectangle(-5, -5, 200, 30, XWindow::White); // erase it after 3 secs
	}
}

// display the original board on the graphic window; if reset, then clear out middle slots
void Game::displayOrigSetup(bool reset)
{
	// the black pieces
	window->drawString(72, 77, "r");
	window->drawString(122, 77, "n");
	window->drawString(172, 77, "b");
	window->drawString(222, 77, "q");
	window->drawString(272, 77, "k");
	window->drawString(322, 77, "b");
	window->drawString(372, 77, "n");
	window->drawString(422, 77, "r");
	for (int i = 1; i <= 8; ++i)
	{
		window->drawString(22 + (50 * i), 127, "p");
		window->drawString(22 + (50 * i), 377, "P");
	}
	// the white pieces
	window->drawString(72, 427, "R");
	window->drawString(122, 427, "N");
	window->drawString(172, 427, "B");
	window->drawString(222, 427, "Q");
	window->drawString(272, 427, "K");
	window->drawString(322, 427, "B");
	window->drawString(372, 427, "N");
	window->drawString(422, 427, "R");
	// clear out middle slots if board resets
	if (reset)
	{
		for (int y = 2; y < 6; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				fill(x, y);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////

// initializes a board on the graphics window as well as its pieces and sets up the board
void Game::init()
{
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 8; ++j)
		{
			// retain the checkerboard pattern
			if ((i + j) % 2)
			{
				window->fillRectangle(50 * i, 50 * j, 50, 50, XWindow::Cyan);
			}
			else
			{
				window->fillRectangle(50 * i, 50 * j, 50, 50, XWindow::White);
			}
		}
	}
	// draw the borders of the board
	window->drawLine(50, 50, 450, 50);
	window->drawLine(50, 50, 50, 450);
	window->drawLine(450, 450, 450, 50);
	window->drawLine(450, 450, 50, 450);
	for (int i = 1; i <= 8; ++i)
	{
		// draw the row indices and column indices on the graphic board
		string s1{"a"};
		s1[0] += i - 1;
		string s2{"0"};
		s2[0] += i;
		window->drawString(22 + (50 * i), 40, s1);
		window->drawString(22 + (50 * i), 470, s1);
		window->drawString(35, 27 + (50 * (9 - i)), s2);
		window->drawString(460, 27 + (50 * (9 - i)), s2);
	}
	// "original-setup" the board
	board->oSetup();
	displayOrigSetup(false); // display the original board on the graphic window; if reset, then clear out middle slots
}

// updates the graphics and text display
void Game::update()
{
	// display text
	printBoard();
	// update window grphics here
	// extract most recent move from history
	if (history.size() == 0)
	{ // if it's empty return
		return;
	}
	Move *move = (history.back()).get();
	// extract position data pos1 to pos2
	int oldCol = move->getPos1x();
	int oldRow = move->getPos1y();
	int newCol = move->getPos2x();
	int newRow = move->getPos2y();
	// extract type of move
	string type = move->getType();
	// update graphics accordingly -
	if (type == "normal" || type == "capture")
	{						  // if the move type is "normal" or "capture",
		fill(newCol, newRow); // erase both the "from" square and the "to" square
		fill(oldCol, oldRow);
		string rep = board->getPiece(newCol, newRow)->getRep();
		drawPiece(rep, newCol, newRow); // "move" the piece in the graphic display
	}
	else if (type == "castle")
	{ // if the move type is "castle"
		if ((newCol - oldCol) == 2)
		{							  // if the king moved right
			fill(newCol + 1, newRow); // erase corner square
			fill(oldCol, oldRow);	  // erase original square
			// draw king and rook in right positions
			string king = board->getPiece(newCol, newRow)->getRep();
			drawPiece(king, newCol, newRow);
			string rook = board->getPiece(newCol - 1, newRow)->getRep();
			drawPiece(rook, newCol - 1, newRow);
		}
		else if ((newCol - oldCol) == -2)
		{ 							  // if the king moved left
			fill(newCol - 2, newRow); // erase corner square
			fill(oldCol, oldRow);	  // erase original square
			// draw king and rook in right positions
			string king = board->getPiece(newCol, newRow)->getRep();
			drawPiece(king, newCol, newRow);
			string rook = board->getPiece(newCol + 1, newRow)->getRep();
			drawPiece(rook, newCol + 1, newRow);
		}
		// distinguish between types of castles
		// based off positiong info
	}
	else if (type == "promotion")
	{
		fill(newCol, newRow); // erase both squares
		fill(oldCol, oldRow);
		string rep = move->getPT();
		drawPiece(rep, newCol, newRow);
		// clear both squares
		// redraw to promoted piece
	}
	else if (type == "promocap")
	{
		fill(newCol, newRow); // erase both squares
		fill(oldCol, oldRow);
		string rep = move->getPT();
		drawPiece(rep, newCol, newRow);
		// clear both squares
		// redraw to promoted piece
	}
	else
	{ // (type == "enpassant")
		// clear oldPos
		fill(oldCol, oldRow);
		// erase at newPosx, oldPosy (location of capt pawn)
		fill(newCol, oldRow);
		// draw pawn in newPos
		string rep = board->getPiece(newCol, newRow)->getRep();
		drawPiece(rep, newCol, newRow);
	}
}

// resets the board to start a new game
// occurs after resign, checkmate, stalemate
void Game::reset()
{
	mode = "menu"; // go to menu mode
	whitemoves = true; // white moves first
	p1 = nullptr; // players are uninitalized
	p2 = nullptr;
	history.clear(); // clear the move history
	board = unique_ptr<twoPlayerBoard>{new twoPlayerBoard}; // make a new board
	board->oSetup(); // "original-setup" the board
	displayOrigSetup(true); // display it on graphics and output
	cout << "Board reset. Please enter set-up mode, start a new game, ";
	cout << "or press Crtl + D to quit." << endl; // output info
}

// handles a single command at a time
// game, move, setup, or resign
void Game::handleEvents()
{
	string line;
	if (!getline(cin, line))
	{
		// crtl+D to quit program
		isRunning = false;
		return;
	}
	stringstream linestream(line);
	string command;
	linestream >> command; // read a command
	// initial mode
	if (mode == "menu")
	{ 
		if (command == "game")
		{ 
			string white;
			string black;
			linestream >> white >> black; // read in "human" or "computer[#]" types
			// check player types
			int whiteLevel = isComputer(white); // get computer levels or 0
			int blackLevel = isComputer(black);
			if ((white == "human" || whiteLevel) && (black == "human" || blackLevel))
			{
				if (white == "human")
				{ // if human make p1 point to human
					p1 = unique_ptr<Human>{new Human{0}};
				}
				else
				{ // if computer make p1 point to it's respective level computer (One, Two, Three)
					if (whiteLevel == 1)
					{
						p1 = unique_ptr<One>{new One{0, whiteLevel}};
					}
					else if (whiteLevel == 2)
					{
						p1 = unique_ptr<Two>{new Two{0, whiteLevel}};
					}
					else //(whiteLevel == 3)
					{
						p1 = unique_ptr<Three>{new Three{0, whiteLevel}};
					}
				}
				if (black == "human")
				{ // if human make p2 point to human
					p2 = unique_ptr<Human>{new Human{1}};
				}
				else
				{ // if computer make p2 point to it's respective level computer (One, Two, Three)
					if (blackLevel == 1)
					{
						p2 = unique_ptr<One>{new One{1, blackLevel}};
					}
					else if (blackLevel == 2)
					{
						p2 = unique_ptr<Two>{new Two{1, blackLevel}};
					}
					else // if (blackLevel == 3)
					{
						p2 = unique_ptr<Three>{new Three{1, blackLevel}};
					}
				}
			}
			else
			{ 
				throw runtime_error{"Invalid player type. Must be 'human' or 'computer[1-4]'\nPlease re-enter game start command."};
			}
			// begin the game
			mode = "game";
			p1->init(board.get(), p2.get()); // initialize the players
			p2->init(board.get(), p1.get());
			p1->claimPieces(); // make the players obtain their pieces (shared ownership)
			p2->claimPieces();
			/*
			p1->print(); // DEBUG
			p2->print();
			*/
			updateSt();
			cout << "Started new game!" << endl;
			return; // return
		}
		else if (command == "setup")
		{ 
			mode = "setup"; // set mode to setup
			cout << "Entered set up mode..." << endl;
			return;
		}
		else
		{ 
			throw runtime_error{"Unrecognized command. Please try again."};
		}
		// assumes that game has started and board has been set up
	}
	else if (mode == "game")
	{ 
		if (command == "resign")
		{ 
			if (whitemoves)
			{ // if white moves, black wins
				score->blackWin();
				displayWin(false);
			}
			else
			{ // else, white wins
				score->whiteWin();
				displayWin(true);
			}
			reset(); // reset the board
		}
		else if (command == "move")
		{ // if the command is "move"
		if (whitemoves)
			{ // white's turn
				if (p1->getType() == 0)
				{
					// human case
					string from;
					string to;
					linestream >> from >> to; // get "from" and "to" move positions
					if (isValidPosition(from) && isValidPosition(to))
					{
						int oldCol = from[0] - 'a';
						int oldRow = '8' - from[1];
						int newCol = to[0] - 'a';
						int newRow = '8' - to[1];
						pair<int, string> status = p1->move(oldCol, oldRow, newCol, newRow);
						// determine what kind of move it is, and move it if it is valid
						if (status.first == 0)
						{ // if it's invalid
							throw runtime_error{"Illegal move attempted. Please try another."};
						}
						else if (status.first == 1)
						{ // basic move
							resetRecents(); // reset the recency of the pieces
							if (board->getPiece(newCol, newRow)->getRep() == "P")
							{
								if (oldRow - newRow == 2)
								{ // if it's a pawn that moved 2 pieces, set it's recency
									board->getPiece(newCol, newRow)->setRecent();
								}
							}
							// store the Normal in history
							history.emplace_back(unique_ptr<Normal>{new Normal{oldCol, oldRow, newCol, newRow}});
						}
						else if (status.first == 2)
							{ // move is a capture
								resetRecents(); // reset the recency of the pieces
								// store the Capture in history
								history.emplace_back(unique_ptr<Capture>{new Capture{oldCol, oldRow, newCol, newRow, status.second}});
							}
						else if (status.first == 3)
							{ // move is a castle
								resetRecents(); // reset the recency of the pieces
								// store the Castle in history
								history.emplace_back(unique_ptr<Castle>{new Castle{oldCol, oldRow, newCol, newRow}});
							}
						else if (status.first == 4)
							{ // move is a promotion w/o capture
								string promoType;
								linestream >> promoType; // read the promotion type
								if (promoType == "R" || promoType == "N" || promoType == "B" || promoType == "Q")
								{ // check if valid type
									resetRecents(); // reset the recency of the pieces
									// store the Promotion in history
									history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, promoType}});
									board->insertP(promoType, to); // insert the promotype piece into board
									p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								}
								else
								{
									throw runtime_error{"Illegal promotion type attempted. Please try another."};
								}
							}
						else if (status.first == 5)
							{ // move is a promotion w/ capture
								string promoType;
								linestream >> promoType; // read the promotion type
								if (promoType == "R" || promoType == "N" || promoType == "B" || promoType == "Q")
								{ // check if valid type
									resetRecents(); // reset the recency of the pieces
									// store the PromotionCapture in history
									history.emplace_back(unique_ptr<PromotionCapture>{new PromotionCapture{oldCol, oldRow, newCol, newRow, promoType, status.second}});
									board->insertP(promoType, to); // insert the promotype piece into board
									p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								}
								else
								{
									throw runtime_error{"Illegal promotion type attempted. Please try another."};
								}
							}
						else if (status.first == 6)
						{ // move is enpassant
								resetRecents(); // reset the recency of the pieces
								// store the EnPassant in history
								history.emplace_back(unique_ptr<EnPassant>{new EnPassant{oldCol, oldRow, newCol, newRow}});
							}
					}
					else
					{ // move unrecognized
						throw runtime_error{"Unrecognized move. Please re-enter."};
					}
				}
				else
				{ // computer case
					int oldCol = 0;
					int oldRow = 0;
					int newCol = 0;
					int newRow = 0;
					std::pair<int, std::string> status = p1->move(oldCol, oldRow, newCol, newRow);
					// determine what kind of move it is, and move it if it is valid, update oldCol, oldRow, newCol, newRow
					if (status.first == 0)
					{ // if it's invalid
						throw runtime_error{"Illegal move attempted. Please try another."};
					}
					else if (status.first == 1)
					{ // basic move
						resetRecents(); // reset the recency of the pieces
						if (board->getPiece(newCol, newRow)->getRep() == "P")
						{
							if (oldRow - newRow == 2)
							{ // if it's a pawn that moved 2 pieces, set it's recency
								board->getPiece(newCol, newRow)->setRecent();
							}
						}
						// store the Normal in history
						history.emplace_back(unique_ptr<Normal>{new Normal{oldCol, oldRow, newCol, newRow}});
					}
					else if (status.first == 2)
					{ // move is a capture
						resetRecents(); // reset the recency of the pieces
						// store the Capture in history
						history.emplace_back(unique_ptr<Capture>{new Capture{oldCol, oldRow, newCol, newRow, status.second}});
					}
					else if (status.first == 3)
					{ // move is a castle
						resetRecents(); // reset the recency of the pieces
						// store the Castle in history
						history.emplace_back(unique_ptr<Castle>{new Castle{oldCol, oldRow, newCol, newRow}});
					}
					else if (status.first == 4)
					{ // move is a promotion w/o capture
						int i = rand() % 4;
						// randomize which type to promote to
						if (i == 0)
						{
							string xStr = string(1, newCol + 'a');
							string yStr = to_string(8 - newRow);
							string strPos = xStr + yStr;
							resetRecents(); // reset the recency of the pieces
							board->insertP("R", strPos); // insert the promotype piece into board
							p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
							// store the Promotion in history
							history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "R"}});
						}
						else if (i == 1)
						{
							string xStr = string(1, newCol + 'a');
							string yStr = to_string(8 - newRow);
							string strPos = xStr + yStr;
							resetRecents(); // reset the recency of the pieces
							board->insertP("N", strPos); // insert the promotype piece into board
							p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
							// store the Promotion in history
							history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "N"}});
						}
						else if (i == 2)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("B", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "B"}});
							}
						else if (i == 3)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("Q", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "Q"}});
							}
					}
					else if (status.first == 5)
						{ // move is a promotion w/ capture
							int i = rand() % 4;
							// randomize which type to promote to
							if (i == 0)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("R", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "R", status.second}});
							}
							else if (i == 1)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("N", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "N", status.second}});
							}
							else if (i == 2)
							{

								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("B", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "B", status.second}});
							}
							else if (i == 3)
							{

								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("Q", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "Q", status.second}});
							}
						}
					else if (status.first == 6)
						{ // move is enpassant
							resetRecents(); // reset the recency of the pieces
							// store the EnPassant in history
							history.emplace_back(unique_ptr<EnPassant>{new EnPassant{oldCol, oldRow, newCol, newRow}});
						}
				}
				// black now moves
				whitemoves = false;
			}
			else
				{ // black's turn
					if (p2->getType() == 0)
					{
						// human case
						string from;
						string to;
						linestream >> from >> to; // get "from" and "to" move positions
						if (isValidPosition(from) && isValidPosition(to))
						{
							int oldCol = from[0] - 'a';
							int oldRow = '8' - from[1];
							int newCol = to[0] - 'a';
							int newRow = '8' - to[1];
							std::pair<int, std::string> status = p2->move(oldCol, oldRow, newCol, newRow);
							// determine what kind of move it is, and move it if it is valid
							if (status.first == 0)
							{ // if it's invalid
								throw runtime_error{"Illegal move attempted. Please try another."};
							}
							else if (status.first == 1)
							{ // basic move
								resetRecents(); // reset the recency of the pieces
								if (board->getPiece(newCol, newRow)->getRep() == "p")
								{
									if (newRow - oldRow == 2)
									{ // if it's a pawn that moved 2 pieces, set it's recency
										board->getPiece(newCol, newRow)->setRecent();
									}
								}
								// store the Normal in history
								history.emplace_back(unique_ptr<Normal>{new Normal{oldCol, oldRow, newCol, newRow}});
							}
							else if (status.first == 2)
							{ // move is a capture
								resetRecents(); // reset the recency of the pieces
								// store the Capture in history
								history.emplace_back(unique_ptr<Capture>{new Capture{oldCol, oldRow, newCol, newRow, status.second}});
							}
							else if (status.first == 3)
							{ // move is a castle
								resetRecents(); // reset the recency of the pieces
								// store the Castle in history
								history.emplace_back(unique_ptr<Castle>{new Castle{oldCol, oldRow, newCol, newRow}});
							}
							else if (status.first == 4)
							{ // move is a promotion w/o capture
								string promoType;
								linestream >> promoType; // read the promotion type
								if (promoType == "r" || promoType == "n" || promoType == "b" || promoType == "q")
								{ // check if valid type
									resetRecents(); // reset the recency of the pieces
									// store the Promotion in history
									history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, promoType}});
									board->insertP(promoType, to); // insert the promotype piece into board
									p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								}
								else
								{
									throw runtime_error{"Illegal promotion type attempted. Please try another."};
								}
							}
							else if (status.first == 5)
							{ // move is a promotion w/ capture
								string promoType;
								linestream >> promoType; // read the promotion type
								if (promoType == "r" || promoType == "n" || promoType == "b" || promoType == "q")
								{ // check if valid type
									resetRecents(); // reset the recency of the pieces
									// store the PromotionCapture in history
									history.emplace_back(unique_ptr<PromotionCapture>{new PromotionCapture{oldCol, oldRow, newCol, newRow, promoType, status.second}});
									board->insertP(promoType, to); // insert the promotype piece into board
									p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								}
								else
								{
									throw runtime_error{"Illegal promotion type attempted. Please try another."};
								}
							}
							else if (status.first == 6)
							{ // move is enpassant
								resetRecents(); // reset the recency of the pieces
								// store the EnPassant in history
								history.emplace_back(unique_ptr<EnPassant>{new EnPassant{oldCol, oldRow, newCol, newRow}});
							}
						}
						else
						{ 
							throw runtime_error{"Unrecognized move. Please re-enter."};
						}
					}
					else
					{ // computer case
						int oldCol = 0;
						int oldRow = 0;
						int newCol = 0;
						int newRow = 0;
						std::pair<int, std::string> status = p2->move(oldCol, oldRow, newCol, newRow);
						// determine what kind of move it is, and move it if it is valid, update oldCol, oldRow, newCol, newRow
						if (status.first == 0)
						{ // invalid move
							throw runtime_error{"Illegal move attempted. Please try another."};
						}
						else if (status.first == 1)
						{ // basic move
							resetRecents(); // reset the recency of the pieces
							if (board->getPiece(newCol, newRow)->getRep() == "p")
							{
								if (newRow - oldRow == 2)
								{ // if it's a pawn that moved 2 pieces, set it's recency
									board->getPiece(newCol, newRow)->setRecent();
								}
							}
							// store the Normal in history
							history.emplace_back(unique_ptr<Normal>{new Normal{oldCol, oldRow, newCol, newRow}});
						}
						else if (status.first == 2)
						{ // move is a capture
							resetRecents(); // reset the recency of the pieces
							// store the Capture in history
							history.emplace_back(unique_ptr<Capture>{new Capture{oldCol, oldRow, newCol, newRow, status.second}});
						}
						else if (status.first == 3)
						{ // move is a castle
							resetRecents(); // reset the recency of the pieces
							// store the Castle in history
							history.emplace_back(unique_ptr<Castle>{new Castle{oldCol, oldRow, newCol, newRow}});
						}
						else if (status.first == 4)
						{ // move is a promotion w/o capture
							int i = rand() % 4;
							// randomize which type to promote to
							if (i == 0)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("r", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "r"}});
							}
							else if (i == 1)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("n", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "n"}});
							}
							else if (i == 2)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("b", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "b"}});
							}
							else if (i == 3)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("q", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<Promotion>{new Promotion{oldCol, oldRow, newCol, newRow, "q"}});
							}
						}
						else if (status.first == 5)
						{ // move is a promotion w/ capture
							int i = rand() % 4;
							// randomize which type to promote to
							if (i == 0)
							{
								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("r", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player

								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "r", status.second}});
							}
							else if (i == 1)
							{

								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("n", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "n", status.second}});
							}
							else if (i == 2)
							{

								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("b", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "b", status.second}});
							}
							else if (i == 3)
							{

								string xStr = string(1, newCol + 'a');
								string yStr = to_string(8 - newRow);
								string strPos = xStr + yStr;
								resetRecents(); // reset the recency of the pieces
								board->insertP("q", strPos); // insert the promotype piece into board
								p1->addToPieces(board->sharePiece(newCol, newRow)); // add it to the player
								// store the Promotion in history
								history.emplace_back(unique_ptr<PromotionCapture>{
									new PromotionCapture{oldCol, oldRow, newCol, newRow, "q", status.second}});
							}
						}
						else if (status.first == 6)
						{ // move is enpassant
							resetRecents(); // reset the recency of the pieces
							// store the EnPassant in history
							history.emplace_back(unique_ptr<EnPassant>{new EnPassant{oldCol, oldRow, newCol, newRow}});
						}
					}
					// white now moves
					whitemoves = true;
				}
			int  end = updateSt();
			if (end == 1)
			{
				// if the player that is about to move
				// is checkmated
				if (whitemoves)
				{ // if white moves, black wins
					score->blackWin();
					displayWin(false);
					reset(); // reset the board
					return;
				}
				else
				{ // if black moves, white wins
					score->whiteWin();
					displayWin(true);
					reset(); // reset the board
					return;
				}
			}
			else if (end == 2)
			{
				// if a stalemate occured
				score->tie(); // set the score a tie
				displayStalemate();
				reset(); // reset the board
				return;
			}
		}
		else if (command == "setup")
		{ 
			throw runtime_error{"ERROR: setup can only be called before a game has started."};
		}
		else
		{ 
			throw runtime_error{"ERROR: Invalid game command."};
		}
	}
	else if (mode == "setup")
	{ 
		cout << "Current Board Configuration:" << endl;
		this->update(); // update the graphics and text display
		if (command == "+")
		{ // if command is +
			string piece;
			string position;
			if (linestream >> piece >> position) // read piece and position
				;
			if (isValidPiece(piece) && isValidPosition(position))
			{ // if piece and position are valid
				board->insertP(piece, position); // insert it on board
				drawPiece(piece, position[0] - 'a', '8' - position[1]); // draw it on board
				cout << "Inserted piece at: " << position << endl;
				return;
			}
			else
			{ 
				throw runtime_error{"ERROR: Invalid. Must be [a-h][1-8] and piece r, n, b, q, k, p, R, N, B, Q, K, P"};
			}
		}
		else if (command == "-")
		{ 
			string position;
			if (linestream >> position);
			if (isValidPosition(position))
			{ // if position is valid
				board->removeP(position); // remove it on board
				fill(position[0] - 'a', '8' - position[1]); // remove it on board graphic
				cout << "Removed piece at: " << position << endl;
				return;
			}
			else
			{ 
				throw runtime_error{"ERROR: Invalid position. Must be [a-h][1-8]"};
			}
		}
		else if (command == "=")
		{ 
		  // set starting mover to color
			string color;
			if (linestream >> color)
				;
			if (color == "white")
			{
				whitemoves = true;
				return;
			}
			else if (color == "black")
			{
				whitemoves = false;
				return;
			}
			else
			{
				throw runtime_error{"Invalid color, please try again."};
			}
		}
		else if (command == "done")
		{ 
			// verify the board
			if (board->verify())
			{ // if setup is OK return to menu
				mode = "menu";
				cout << "Game-setup Complete!" << endl;
				return;
			}
			else
			{ 
				throw runtime_error{"ERROR: Setup conditions are not satisfied.\nPlease continue set-up"};
			}
		}
		else
		{
			throw runtime_error{"Unrecognized Command."};
		}
	}
}

// quits the game and prints final score
void Game::quit()
{
	// print winning results
	if (score)
	{
		score->printScore();
	}
	cout << endl
		 << "Thanks for playing!" << endl;
}

// returns true if game is running
bool Game::running()
{
	return isRunning;
}

// resets the recency of the pieces
void Game::resetRecents()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (board->getPiece(i, j))
			{
				Piece *p = board->getPiece(i, j);
				p->resetRecent();
			}
		}
	}
}

int Game::updateSt() {
	int end;
	p1->unsetStatus(); // unset the status fields of each piece
	p2->unsetStatus();
	if (whitemoves)
	{ // if white moves, update all the status fields of p1
		end = p1->checkStatus();
	}
	else
	{ // else, update all the status fields of p2
		end = p2->checkStatus();
	}
	return end;
}

