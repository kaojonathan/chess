CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla
OBJECTS = main.o board.o twoPlayerBoard.o bishop.o queen.o king.o \
knight.o rook.o pawn.o piece.o computer.o human.o one.o two.o three.o
# history, player classes?
# need to figure out how to compile the GUI within make file
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}