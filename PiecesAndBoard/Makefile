CXX = g++
CXXFLAGS = -std=c++14 -Wall
OBJECTS = piece.o bishop.o king.o pawn.o rook.o knight.o queen.o \
board.o twoPlayerBoard.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = gameParts

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
