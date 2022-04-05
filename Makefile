CXX = g++
CXXFLAGS = -std=c++14 -Wall -lX11
OBJECTS = Graphics/window.o Graphics/XWindowImpl.o Interface/Game.o \
Pieces/bishop.o Board/board.o Pieces/knight.o Pieces/king.o \
Pieces/pawn.o Pieces/piece.o Pieces/queen.o Pieces/rook.o \
Board/twoPlayerBoard.o Players/computer.o Players/human.o \
Players/one.o Players/player.o Players/three.o Players/two.o main.o Interface/score.o \
Pieces/Move/promotion.o Pieces/Move/normal.o Pieces/Move/move.o \
Pieces/Move/enpassant.o Pieces/Move/castle.o Pieces/Move/capture.o Pieces/Move/promotioncap.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = play

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
