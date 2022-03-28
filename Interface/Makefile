CXX = g++
CXXFLAGS = -std=c++14 -Wall
OBJECTS = main.o game.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = interface

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}