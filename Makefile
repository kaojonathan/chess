CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla
OBJECTS = main.o board.o twoPlayerBoard.o bishop.o queen.o king.o \
knight.o rook.o pawn.o piece.o computer.o human.o game.o
# history
# need to figure out how to compile the GUI within make file
# need to fix computer classes one two three computer
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}