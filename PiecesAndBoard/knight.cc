#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "knight.h"
#include "board.h"
#include "../Players/player.h"
using namespace std;

Knight::Knight(int side, int x, int y, Board * board) : Piece{ side, x, y, board} {
	value = 3;
	representation = (side == 0) ? "N" : "n";
}

// return all positions the Knight at (col, row) can move to, not include positions out of bound 
vector<std::pair<int, int>> Knight::getPos(int col, int row) {
	vector<std::pair<int,int>> res{};
	for (int i = 1; i <= 2; i += 1){
		pair<int,int>curPos{col+i,row+(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
<<<<<<< HEAD
		curPos = pair<int,int>{col+i,row-(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
		curPos = pair<int,int>{col-i,row-(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
		curPos = pair<int,int>{col-i,row+(3-i)};
=======
		curPos = pair<int, int>{col+i,row-(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
		curPos = pair<int, int>{col-i,row-(3-i)};
		if (validPos(curPos)) res.emplace_back(curPos);
		curPos = pair<int, int>{col-i,row+(3-i)};
>>>>>>> 3af86c7f85ca405a58971bbcffe14f119919c7fd
		if (validPos(curPos)) res.emplace_back(curPos);
	}
	return res;
}

// return a vector of piece that the Knight at pos = (col, row) can capture
vector<Piece *> Knight::attackable(pair<int, int> position){
	vector<Piece *> res{};
	for (auto pos : getPos(position.first, position.second)){
		Piece *target = gameBoard->getPiece(pos.first, pos.second);
		if (target && side != target->getSide()) {
			res.emplace_back(target);
		}
	}
	return res;
}



void Knight::nUpdate()  {
	updateStatus = 1;
	for (auto pos : getPos(x, y)){
		Piece * target = gameBoard->getPiece(pos.first, pos.second);
		if (target) {
			if (enemyKing(target)) {
				checkRoute.emplace_back(pair<int, int>{x,y});
				enemy->kingCheckedBy(this);
			}
			else if (target->getSide() != side) targets.emplace_back(pos);
		}
		else {
			moves.emplace_back(pos);
		}
	}
}

/*
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
*/