CXX = g++
CXXFLAGS = -std=c++14 -Wall -lX11
OBJECTS = window.o chessGUI.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = graphics

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
