# Usage:
#   make: compile all executables
#   make clean: remove all object files and executables
#   make main: compile the main executable
#   make main2: compile the main2 executable
#   make suite1: run the tests/suite1.txt with main
#   make suite1 TEST_EXEC=main2: run the tests/suite2.txt with main2
#   make debug: print available executables and test suites

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O2 $(shell pkg-config --cflags x11) -I/opt/X11/include
LDFLAGS = $(shell pkg-config --libs x11) -I/opt/X11/include -L/opt/X11/lib -lX11

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

# Dependency files
DEPS = $(SOURCES:.cc=.d)
DEPS += $(EXEC_SOURCES:.cc=.d)

.PHONY: all clean
# Default target: all executables
all: clean $(EXEC)

# Rule for linking the executables
$(EXEC): %: $(OBJECTS) %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule for compiling .cc to .o files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for generating dependency files
%.d: %.cc
	$(CXX) -MM $(CXXFLAGS) $< > $@

# Include dependency files
-include $(DEPS)

# Clean rule to remove object files and all executables
clean:
	rm -f $(OBJECTS) $(EXEC_OBJECTS) $(EXEC) $(DEPS)

TEST_EXEC = main
TEST_SUITES = $(basename $(notdir $(wildcard tests/*.txt)))

.PHONY: $(TEST_SUITES)

$(TEST_SUITES):
	@echo "Running test suite: $@"
	./runSuite.sh tests/$@.txt ./$(TEST_EXEC)

debug:
	@echo "Available executables: $(EXEC)"
	@echo "Available test suites: $(TEST_SUITES)"