CXX = g++
CXXFLAGS = -std=c++14 -Wall -lX11
OBJECTS = piece.o bishop.o king.o pawn.o rook.o knight.o queen.o \
board.o twoPlayerBoard.o human.o computer.o Game.o window.o \
main.o score.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = play

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
