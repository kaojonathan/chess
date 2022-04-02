CXX = g++
CXXFLAGS = -std=c++14 -Wall -lX11
OBJECTS = Graphics/window.o Graphics/XWindowImpl.o Interface/Game.o \
PiecesAndBoard/bishop.o PiecesAndBoard/board.o PiecesAndBoard/knight.o PiecesAndBoard/king.o \
PiecesAndBoard/pawn.o PiecesAndBoard/piece.o PiecesAndBoard/queen.o PiecesAndBoard/rook.o \
PiecesAndBoard/twoPlayerBoard.o Players/computer.o Players/four.o Players/human.o \
Players/one.o Players/player.o Players/three.o Players/two.o main.o score.o \
PiecesAndBoard/Move/promotion.o PiecesAndBoard/Move/normal.o PiecesAndBoard/Move/move.o \
PiecesAndBoard/Move/enpassant.o PiecesAndBoard/Move/castle.o PiecesAndBoard/Move/capture.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = play

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
