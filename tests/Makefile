# Makefile placed in ./tests directory

# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I../src

# Directories
SRC_DIR = ../src
TEST_DIR = .

# Source Files
TEST_SRC = test.cpp testsuite.cpp
SRC_FILES = $(SRC_DIR)/filehandler.cpp $(SRC_DIR)/gradecalculator.cpp

# Object Files
TEST_OBJ = test.o testsuite.o
SRC_OBJ = filehandler.o gradecalculator.o

# All Object Files
ALL_OBJ = $(TEST_OBJ) $(SRC_OBJ)

# Executable Name
TEST_EXEC = test_suite

# Default Target
all: $(TEST_EXEC)

# Link the Executable
$(TEST_EXEC): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(ALL_OBJ)

# Compile Test Source Files
test.o: $(TEST_DIR)/test.cpp ../src/filehandler.h ../src/gradecalculator.h
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/test.cpp -o test.o

testsuite.o: $(TEST_DIR)/testsuite.cpp $(TEST_DIR)/testsuite.h ../src/filehandler.h ../src/gradecalculator.h
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/testsuite.cpp -o testsuite.o

# Compile Source Files from src/
filehandler.o: $(SRC_DIR)/filehandler.cpp $(SRC_DIR)/filehandler.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/filehandler.cpp -o filehandler.o

gradecalculator.o: $(SRC_DIR)/gradecalculator.cpp $(SRC_DIR)/gradecalculator.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/gradecalculator.cpp -o gradecalculator.o

# Clean Target to Remove Compiled Objects and Executable
clean:
	rm -f $(TEST_EXEC) $(ALL_OBJ)

.PHONY: all clean
