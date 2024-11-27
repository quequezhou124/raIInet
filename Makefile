# Usage:
#   make: compile all executables
#   make clean: remove all object files and executables
#   make main: compile the main executable
#   make main2: compile the main2 executable
#   etc.

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O2
LDFLAGS = -lX11

# Define the prefix for the main executable (e.g., main)
EXEC_PREFIX = main
# Get all .cc files that start with EXEC_PREFIX (e.g., main.cc, main_2.cc, etc.)
EXEC_SOURCES = $(wildcard $(EXEC_PREFIX)*.cc)
# Get corresponding object files from EXEC_SOURCES
EXEC_OBJECTS = $(EXEC_SOURCES:.cc=.o)
# All other .cc files except those starting with EXEC_PREFIX
SOURCES = $(filter-out $(EXEC_SOURCES), $(wildcard *.cc))
# Object files for all sources (excluding the main executable sources)
OBJECTS = $(SOURCES:.cc=.o)

# Define the final executable targets (e.g., main, main_2, main_test, etc.)
EXEC = $(basename $(EXEC_SOURCES))

# Default target: all executables
all: $(EXEC)

# Rule for linking the executables
$(EXEC): %: %.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule for compiling .cc to .o files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and all executables
clean:
	rm -f $(OBJECTS) $(EXEC_OBJECTS) $(EXEC)

.PHONY: all clean
