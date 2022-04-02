#ifndef BOARD_H_
#define BOARD_H_
#include "piece.h"
#include <string>

class Board {
	protected:
		virtual void insertNewPiece(std::string validpiece, std::string position) = 0;
		virtual void removePiece(std::string position)= 0;
		virtual Piece* getP(int, int) = 0;
		virtual void movePiece(int x, int y, int newx, int newy) = 0; // setter
		virtual bool validPos (int, int) = 0;
		virtual void set(int x, int y, Piece * p) = 0;

		virtual bool verifySetup() = 0;
		virtual void origSetup() = 0;

	public:
		Board();
		virtual ~Board() = 0;
		bool checkPos(int, int);
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
		void setPiece(int x, int y, Piece * p) {
			set(x,y,p);
		}
		bool verify() {
			return verifySetup();
		}
		void oSetup() {
			origSetup();
		}
};

#endif