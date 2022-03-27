#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "knight.h"
#include "board.h"
using namespace std;

Knight::Knight(bool isWhite) : Piece{ isWhite } {
	if (isWhite) {
		representation = "N";
	}
	else {
		representation = "n";
	}
}



void Knight::updateMovePossibilities()  {
	// knight's availible moves

	if ((x - 1 >= 0) && (y + 2 <= 7)) {
		leftonedowntwo.emplace_back(gameBoard->getPiece(x - 1, y + 2));
	}

	if ((x - 1 >= 0) && (y - 2 >= 0)) {
		leftoneuptwo.emplace_back(gameBoard->getPiece(x - 1, y - 2));
	}


	if ((x + 1 <= 7) && (y + 2 <= 7)) {
		rightonedowntwo.emplace_back(gameBoard->getPiece(x + 1, y + 2));
	}

	if ((x + 1 <= 7) && (y - 2 >= 0)) {
		rightoneuptwo.emplace_back(gameBoard->getPiece(x + 1, y - 2));
	}
	if ((x + 2 <= 7) && (y + 1 <= 7)) {
		downonerighttwo.emplace_back(gameBoard->getPiece(x - 1, y + 2));
	}
	if ((x - 2 >= 0) && (y + 1 <= 7)) {
		downonelefttwo.emplace_back(gameBoard->getPiece(x - 1, y - 2));
	}
	if ((x + 2 <= 7) && (y - 1 >= 0)) {
		uponerighttwo.emplace_back(gameBoard->getPiece(x + 1, y + 2));
	}
	if ((x - 2 >= 0) && (y - 1 >= 0)) {
		uponelefttwo.emplace_back(gameBoard->getPiece(x + 1, y - 2));
	}
}

/* dscan?
bool Knight::kingInCheck(bool isWhite)  {
	for (int i = 0; i < leftoneuptwo.size(); ++i) {

		// for knight, if we hit a non-null pointer, then we stop the loop, since that piece will block its path. 
		// If it's the opposite color's king, it's in check

		if (leftoneuptwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (leftoneuptwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (leftoneuptwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	// same thing for other 7 moves

	for (int i = 0; i < leftonedowntwo.size(); ++i) {

		if (leftonedowntwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (leftonedowntwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (leftonedowntwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	for (int i = 0; i < rightoneuptwo.size(); ++i) {

		if (rightoneuptwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (rightoneuptwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (rightoneuptwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}


	for (int i = 0; i < rightonedowntwo.size(); ++i) {

		if (rightonedowntwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (rightonedowntwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (rightonedowntwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}


	for (int i = 0; i < uponerighttwo.size(); ++i) {

		if (uponerighttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (uponerighttwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (uponerighttwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	for (int i = 0; i < downonerighttwo.size(); ++i) {

		if (downonerighttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (downonerighttwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (downonerighttwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}


	for (int i = 0; i < uponelefttwo.size(); ++i) {

		if (uponelefttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (uponelefttwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (uponelefttwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}

	}

	for (int i = 0; i < downonelefttwo.size(); ++i) {

		if (downonelefttwo[i]) {
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if (downonelefttwo[i]->getRep()[0]== 'k') { // if black king
					if (isWhite) {
						return true;
					}
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if (downonelefttwo[i]->getRep()[0]== 'k') { // if white king
					if (!isWhite) {
						return true;
					}
				}
			}
			break;
		}
	}
	// since no king has been checked, return false
	return false;
}
*/


int Knight::canMove(int x, int y) {
	// first check if the move is valid for any knight to make
	if ((this->x + 2 == x) && (this->y + 1 == y)) { // if we performed a right 2 down 1 move
		if (downonerighttwo.size() == 0) { // if out of bounds do nothing
			return 0;
		}
		else { // otherwise there is either a blank cell or a piece
			if (downonerighttwo[0]) { // not blank cell
				// if opposite color capture the piece	
				if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
					if ((97 <= downonerighttwo[0]->getRep()[0]) && (downonerighttwo[0]->getRep()[0] <= 122)) { // if black piece
						// capture the piece and move
						return 2;
					}
					else { // otherwise the piece is white and so dont move!
						return 0;
					}
				}
				else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
					if ((65 <= downonerighttwo[0]->getRep()[0]) && (downonerighttwo[0]->getRep()[0] <= 90)) { // if white piece
	// capture the piece and move
						return 2;
					}
					else { // otherwise the piece is black and so dont move!
						return 0;
					}
				}
			}
			else { // blank cell, move the piece
				return 1;
			}
		}
	}
	else if ((this->x + 2 == x) && (this->y - 1 == y)) { // if we performed a right 2 up 1 move
		if (uponerighttwo.size() == 0) { // if out of bounds do nothing
			return 0;
		}
		else { // otherwise there is either a blank cell or a piece
			if (uponerighttwo[0]) { // not blank cell
				// if opposite color capture the piece
				if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
					if ((97 <= uponerighttwo[0]->getRep()[0]) && (uponerighttwo[0]->getRep()[0] <= 122)) { // if black piece
						// capture the piece and move
						return 2;
					}
					else { // otherwise the piece is white and so dont move!
						return 0;
					}
				}
				else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
					if ((65 <= uponerighttwo[0]->getRep()[0]) && (uponerighttwo[0]->getRep()[0] <= 90)) { // if white piece
	// capture the piece and move
						return 2;
					}
					else { // otherwise the piece is black and so dont move!
						return 0;
					}
				}
			}
			else { // blank cell, move the piece
				return 1;
			}
		}
	}
	else if ((this->x - 2 == x) && (this->y + 1 == y)) { // if we performed a left 2 down 1 move
	if (downonelefttwo.size() == 0) { // if out of bounds do nothing
		return 0;
	}
	else { // otherwise there is either a blank cell or a piece
		if (downonelefttwo[0]) { // not blank cell
			// if opposite color capture the piece
			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)
				if ((97 <= downonelefttwo[0]->getRep()[0]) && (downonelefttwo[0]->getRep()[0] <= 122)) { // if black piece
					// capture the piece and move
					return 2;
				}
				else { // otherwise the piece is white and so dont move!
					return 0;
				}
			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)
				if ((65 <= downonelefttwo[0]->getRep()[0]) && (downonelefttwo[0]->getRep()[0] <= 90)) { // if white piece
// capture the piece and move
					return 2;
				}
				else { // otherwise the piece is black and so dont move!
					return 0;
				}
			}
		}
		else { // blank cell, move the piece
			return 1;
		}
	}
	}
	else if ((this->x - 2 == x) && (this->y - 1 == y)) { // if we performed a left 2 up 1 move


	if (uponelefttwo.size() == 0) { // if out of bounds do nothing

		return 0;

	}
	else { // otherwise there is either a blank cell or a piece

		if (uponelefttwo[0]) { // not blank cell

			// if opposite color capture the piece

			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)

				if ((97 <= uponelefttwo[0]->getRep()[0]) && (uponelefttwo[0]->getRep()[0] <= 122)) { // if black piece


					// capture the piece and move

					return 2;



				}
				else { // otherwise the piece is white and so dont move!


					return 0;



				}



			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)

				if ((65 <= uponelefttwo[0]->getRep()[0]) && (uponelefttwo[0]->getRep()[0]<= 90)) { // if white piece

// capture the piece and move


					return 2;


				}
				else { // otherwise the piece is black and so dont move!

					return 0;



				}





			}





		}
		else { // blank cell, move the piece


			return 1;



		}






	}


	} else if ((this->x + 1 == x) && (this->y + 2 == y)) { // if we performed a right 1 down 2 move


		if (rightonedowntwo.size() == 0) { // if out of bounds do nothing

			return 0;

		}
		else { // otherwise there is either a blank cell or a piece

			if (rightonedowntwo[0]) { // not blank cell

				// if opposite color capture the piece

				if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)

					if ((97 <= rightonedowntwo[0]->getRep()[0]) && (rightonedowntwo[0]->getRep()[0] <= 122)) { // if black piece


						// capture the piece and move

						return 2;



					}
					else { // otherwise the piece is white and so dont move!


						return 0;



					}



				}
				else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)

					if ((65 <= rightonedowntwo[0]->getRep()[0]) && (rightonedowntwo[0]->getRep()[0]<= 90)) { // if white piece

	// capture the piece and move


						return 2;


					}
					else { // otherwise the piece is black and so dont move!

						return 0;



					}





				}





			}
			else { // blank cell, move the piece


				return 1;



			}






		}

	}
	else if ((this->x + 1 == x) && (this->y - 2 == y)) { // if we performed a right 1 up 2 move

	if (rightoneuptwo.size() == 0) { // if out of bounds do nothing

		return 0;

	}
	else { // otherwise there is either a blank cell or a piece

		if (rightoneuptwo[0]) { // not blank cell

			// if opposite color capture the piece

			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)

				if ((97 <= rightoneuptwo[0]->getRep()[0]) && (rightoneuptwo[0]->getRep()[0]<= 122)) { // if black piece


					// capture the piece and move

					return 2;



				}
				else { // otherwise the piece is white and so dont move!


					return 0;



				}



			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)

				if ((65 <= rightoneuptwo[0]->getRep()[0]) && (rightoneuptwo[0]->getRep()[0]<= 90)) { // if white piece

// capture the piece and move


					return 2;


				}
				else { // otherwise the piece is black and so dont move!

					return 0;



				}





			}





		}
		else { // blank cell, move the piece


			return 1;



		}






	}

	}
	else if ((this->x - 1 == x) && (this->y + 2 == y)) { // if we performed a left 1 down 2 move

	if (leftonedowntwo.size() == 0) { // if out of bounds do nothing

		return 0;

	}
	else { // otherwise there is either a blank cell or a piece

		if (leftonedowntwo[0]) { // not blank cell

			// if opposite color capture the piece

			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)

				if ((97 <= leftonedowntwo[0]->getRep()[0]) && (leftonedowntwo[0]->getRep()[0]<= 122)) { // if black piece


					// capture the piece and move

					return 2;



				}
				else { // otherwise the piece is white and so dont move!


					return 0;



				}



			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)

				if ((65 <= leftonedowntwo[0]->getRep()[0]) && (leftonedowntwo[0]->getRep()[0]<= 90)) { // if white piece

// capture the piece and move


					return 2;


				}
				else { // otherwise the piece is black and so dont move!

					return 0;



				}





			}





		}
		else { // blank cell, move the piece


			return 1;



		}






	}

	}
	else if ((this->x - 1 == x) && (this->y - 2 == y)) { // if we performed a left 1 up 2 move

	if (leftoneuptwo.size() == 0) { // if out of bounds do nothing

		return 0;

	}
	else { // otherwise there is either a blank cell or a piece

		if (leftoneuptwo[0]) { // not blank cell

			// if opposite color capture the piece

			if ((65 <= representation[0]) && (representation[0] <= 90)) { // capital letter (white)

				if ((97 <= leftoneuptwo[0]->getRep()[0]) && (leftoneuptwo[0]->getRep()[0]<= 122)) { // if black piece


					// capture the piece and move

					return 2;



				}
				else { // otherwise the piece is white and so dont move!


					return 0;



				}



			}
			else if ((97 <= representation[0]) && (representation[0] <= 122)) { // lower case letter (black)

				if ((65 <= leftoneuptwo[0]->getRep()[0]) && (leftoneuptwo[0]->getRep()[0]<= 90)) { // if white piece

// capture the piece and move


					return 2;


				}
				else { // otherwise the piece is black and so dont move!

					return 0;



				}





			}





		}
		else { // blank cell, move the piece


			return 1;



		}




	}


	}
	else { // invalid moves for any Knight to make (do nothing?)

		cout << "Invalid move for a Knight..." << endl; // remove this later
		return 0;



	}
	
	

}





















































// helper function that determines of the knight in position (x, y) checks the king
bool Knight::posInCheck(int x, int y) {
	if ((x + 2 > 7) || (y + 1 > 7)) { // down 1 right 2

	}
	else if (gameBoard->getPiece(x + 2, y + 1)) {
		if ((gameBoard->getPiece(x + 2, y + 1)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)
			return true;
		}
		else if ((gameBoard->getPiece(x + 2, y + 1)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}

	if ((x + 2 > 7) || (y - 1 < 0)) { // up 1 right 2

	}
	else if (gameBoard->getPiece(x + 2, y - 1)) {

		if ((gameBoard->getPiece(x + 2, y - 1)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)

			return true;


		}
		else if ((gameBoard->getPiece(x + 2, y - 1)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}

	if ((x - 2 < 0) || (y + 1 > 7)) { // down 1 left 2

	}
	else if (gameBoard->getPiece(x - 2, y + 1)) {

		if ((gameBoard->getPiece(x - 2, y + 1)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)

			return true;


		}
		else if ((gameBoard->getPiece(x - 2, y + 1)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}

	if ((x - 2 < 0) || (y - 1 < 0)) { // up 1 left 2

	}
	else if (gameBoard->getPiece(x - 2, y - 1)) {

		if ((gameBoard->getPiece(x - 2, y - 1)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)

			return true;


		}
		else if ((gameBoard->getPiece(x - 2, y - 1)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}



	if ((x + 1 > 7) || (y + 2 > 7)) { // down 2 right 1

	}
	else if (gameBoard->getPiece(x + 1, y + 2)) {

		if ((gameBoard->getPiece(x + 1, y + 2)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)

			return true;


		}
		else if ((gameBoard->getPiece(x + 1, y + 2)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}

	if ((x + 1 > 7) || (y - 2 < 0)) { // up 2 right 1

	}
	else if (gameBoard->getPiece(x + 1, y - 2)) {

		if ((gameBoard->getPiece(x + 1, y - 2)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)

			return true;


		}
		else if ((gameBoard->getPiece(x + 1, y - 2)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}

	if ((x - 1 < 0) || (y + 2 > 7)) { // down 2 left 1

	}
	else if (gameBoard->getPiece(x - 1, y + 2)) {

		if ((gameBoard->getPiece(x - 1, y + 2)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)

			return true;


		}
		else if ((gameBoard->getPiece(x - 1, y + 2)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}

	if ((x - 1 < 0) || (y - 2 < 0)) { // up 2 left 1

	}
	else if (gameBoard->getPiece(x - 1, y - 2)) {

		if ((gameBoard->getPiece(x - 1, y - 2)->getRep()[0]== 'k') && (this->getSide() == 1)) { // can check the king (black takes white)

			return true;


		}
		else if ((gameBoard->getPiece(x - 1, y - 2)->getRep()[0]== 'k') && (this->getSide() == 0)) { // can check the king (white takes black)

			return true;
		}

	}


	// since no king has been checked, return false

	return false;

}



pair<int, int> Knight::getCheckCoords() {

	if (rightoneuptwo.size() == 1) {
		if (rightoneuptwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (rightoneuptwo[0]->getSide() == 1) { // if black piece
					if (posInCheck(x + 1, y - 2)) { // if the bishop in position (x + 1, y - 2) checks the king

						pair<int, int> coords = { x + 1, y - 2 };
						return coords;
					}
				}
			}
			else { // lower case letter (black)
				if (rightoneuptwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x + 1, y - 2)) { // if the bishop in position (x + 1, y - 2) checks the king

						pair<int, int> coords = { x + 1, y - 2 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x + 1, y - 2)) { // if the bishop in position (x + 1, y - 2) checks the king

				pair<int, int> coords = { x + 1, y - 2 };
				return coords;
			}


		}


	}

	if (leftoneuptwo.size() == 1) {
		if (leftoneuptwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (leftoneuptwo[0]->getSide() == 1) { // if black piece


					if (posInCheck(x - 1, y - 2)) { // if the bishop in position (x - 1, y - 2) checks the king

						pair<int, int> coords = { x - 1, y - 2 };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (leftoneuptwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x - 1, y - 2)) { // if the bishop in position (x - 1, y - 2) checks the king

						pair<int, int> coords = { x - 1, y - 2 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x - 1, y - 2)) { // if the bishop in position (x - 1, y - 2) checks the king

				pair<int, int> coords = { x - 1, y - 2 };
				return coords;
			}

		
		}
	}

	if (rightonedowntwo.size() == 1) {

		if (rightonedowntwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (rightonedowntwo[0]->getSide() == 1) { // if black piece


					if (posInCheck(x + 1, y + 2)) { // if the bishop in position (x + 1, y + 2) checks the king

						pair<int, int> coords = { x + 1, y + 2 };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (rightonedowntwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x + 1, y + 2)) { // if the bishop in position (x + 1, y + 2) checks the king

						pair<int, int> coords = { x + 1, y + 2 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x + 1, y + 2)) { // if the bishop in position (x + 1, y + 2) checks the king

				pair<int, int> coords = { x + 1, y + 2 };
				return coords;
			}


		}

	}

	if (leftonedowntwo.size() == 1) {


		if (leftonedowntwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (leftonedowntwo[0]->getSide() == 1) { // if black piece


					if (posInCheck(x - 1, y + 2)) { // if the bishop in position (x - 1, y + 2) checks the king

						pair<int, int> coords = { x - 1, y + 2 };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (leftonedowntwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x - 1, y + 2)) { // if the bishop in position (x - 1, y + 2) checks the king

						pair<int, int> coords = { x - 1, y + 2 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x - 1, y + 2)) { // if the bishop in position (x - 1, y + 2) checks the king

				pair<int, int> coords = { x - 1, y + 2 };
				return coords;
			}


		}

	}

	if (uponerighttwo.size() == 1) {

		if (uponerighttwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (uponerighttwo[0]->getSide() == 1) { // if black piece


					if (posInCheck(x + 2, y - 1)) { // if the bishop in position (x + 2, y - 1) checks the king

						pair<int, int> coords = { x + 2, y - 1 };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (uponerighttwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x + 2, y - 1)) { // if the bishop in position (x + 2, y - 1) checks the king

						pair<int, int> coords = { x + 2, y - 1 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x + 2, y - 1)) { // if the bishop in position (x + 2, y - 1) checks the king

				pair<int, int> coords = { x + 2, y - 1 };
				return coords;
			}


		}

	}


	if (uponelefttwo.size() == 1) {


		if (uponelefttwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (uponelefttwo[0]->getSide() == 1) { // if black piece


					if (posInCheck(x - 2, y - 1)) { // if the bishop in position (x - 2, y - 1) checks the king

						pair<int, int> coords = { x - 2, y - 1 };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (uponelefttwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x - 2, y - 1)) { // if the bishop in position (x - 2, y - 1) checks the king

						pair<int, int> coords = { x - 2, y - 1 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x - 2, y - 1)) { // if the bishop in position (x - 2, y - 1) checks the king

				pair<int, int> coords = { x - 2, y - 1 };
				return coords;
			}


		}

	}

	if (downonerighttwo.size() == 1) {
		if (downonerighttwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (downonerighttwo[0]->getSide() == 1) { // if black piece


					if (posInCheck(x + 2, y + 1)) { // if the bishop in position (x + 2, y + 1) checks the king

						pair<int, int> coords = { x + 2, y + 1 };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (downonerighttwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x + 2, y + 1)) { // if the bishop in position (x + 2, y + 1) checks the king

						pair<int, int> coords = { x + 2, y + 1 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x + 2, y + 1)) { // if the bishop in position (x + 2, y + 1) checks the king

				pair<int, int> coords = { x + 2, y + 1 };
				return coords;
			}


		}

	}
	if (downonelefttwo.size() == 1) {

		if (downonelefttwo[0]) { // not blank cell
			if (side == 0) { // capital letter (white)
				if (downonelefttwo[0]->getSide() == 1) { // if black piece


					if (posInCheck(x - 2, y + 1)) { // if the bishop in position (x - 2, y + 1) checks the king

						pair<int, int> coords = { x - 2, y + 1 };
						return coords;
					}


				}
			}
			else { // lower case letter (black)
				if (downonelefttwo[0]->getSide() == 0) { // if white piece

					if (posInCheck(x - 2, y + 1)) { // if the bishop in position (x - 2, y + 1) checks the king

						pair<int, int> coords = { x - 2, y + 1 };
						return coords;
					}


				}
			}
		}
		else { // open square

			if (posInCheck(x - 2, y + 1)) { // if the bishop in position (x - 2, y + 1) checks the king

				pair<int, int> coords = { x - 2, y + 1 };
				return coords;
			}


		}

	}

	// if there are no possible move positions that check the king

	pair<int, int> coords = { -1, -1 };
	return coords;

}