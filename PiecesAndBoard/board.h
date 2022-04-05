#ifndef BOARD_H_
#define BOARD_H_
#include "piece.h"
#include <string>
#include <memory>

class Board {
	protected:
		virtual void insertNewPiece(std::string validpiece, std::string position) = 0;
		virtual void removePiece(std::string position)= 0;
		virtual std::shared_ptr<Piece> shareP(int, int) = 0;
		virtual Piece* getP(int, int) = 0;
		virtual void movePiece(int x, int y, int newx, int newy) = 0; 
		virtual bool validPos (int, int) = 0;

		virtual bool verifySetup() = 0;
		virtual void origSetup() = 0;
		virtual void capturePiece(int newx, int newy) = 0;

		virtual void castle(int col, int row) = 0;

	public:
		Board();
		virtual ~Board() = 0;
		bool checkPos(int, int);
		std::shared_ptr<Piece> sharePiece(int x , int y) {
			return shareP(x, y);
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
		bool verify() {
			return verifySetup();
		}
		void oSetup() {
			origSetup();
		}

		void captureP(int newx, int newy) {

			capturePiece(newx, newy);

		}

		void doCastle(int col, int row) {
			castle(col, row);
		}
};

#endif