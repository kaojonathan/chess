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
		virtual void insertNewPiece(std::string validpiece, std::string position) = 0;
		virtual void removePiece(std::string position)= 0;
		virtual Piece* getP(int, int) = 0;
		virtual void movePiece(int x, int y, int newx, int newy) = 0; // setter
		virtual bool validPos (int, int) = 0;
		virtual void set(int x, int y, Piece * p);

	public:
		virtual ~Board();
		bool checkPos(int, int);
		void originalSetup() {
 			origSetup();
		}
		Piece* getPiece(int x , int y) {
			return getP(x, y);
		}
		void moveP(int x, int y, int newx, int newy) {
			movePiece(x, y, newx, newy);
		}
		void removeP(std::string position) {
			removePiece(position);
		}
		void insertP(std::string p, std::string pos) {
			insertNewPiece(p, pos);
		}
		void printBoard() {
			print();
		}
		void setPiece(int x, int y, Piece * p) {
			set(x,y,p);
		}
};

#endif