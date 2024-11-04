CXX = g++                                    # compiler name
CXXFLAGS = -g -std=c++17 -Wall -MMD         # compiler flags
OBJECTS = main.o filehandler.o gradecalculator.o    # objects to compile
EXEC = main                        				# target executable
DEPENDS = ${OBJECTS:.o=.d}                   # substitutes .o with .d

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm -f ${OBJECTS} ${DEPENDS} ${EXEC}
