#ifndef BOARD_H_
#define BOARD_H_
#include "piece.h"
#include <string>

class Board {
	protected:
		// default board set up
		virtual void origSetup() = 0;
		virtual void print() = 0; // get rid of?
		virtual bool end() = 0; // needs implementation
		virtual bool kingInCheck(bool isWhite) = 0;
		virtual void insertNewPiece(std::string validpiece, std::string position) = 0;
		virtual void removePiece(std::string position)= 0;
		virtual bool verifySetup() = 0;
		// will NVI UMP
		virtual void updateBoardMoves() = 0; 
		virtual Piece* getP(int, int) = 0;
		virtual void movePiece(int x, int y, int newx, int newy) = 0; // setter
		virtual bool validPos (int, int) = 0;

	public:
		virtual ~Board();
		bool checkPos(int, int);
		// updates each Piece's possible moves (uses polymorphism)
		void updateBoard() {
			updateBoardMoves();
		}
		Piece* getPiece(int x , int y) {
			getP(x, y);
		}
};

#endif