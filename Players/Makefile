CXX = g++
CXXFLAGS = -std=c++14 -Wall
OBJECTS = computer.o human.o
# levels one two three?
DEPENDS = ${OBJECTS:.o=.d}
EXEC = players

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}