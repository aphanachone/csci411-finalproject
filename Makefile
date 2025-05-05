# Makefile

CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall

# Default: build solver, maker, and referee
all: sudoku_solver sudoku_maker referee

# Build the Sudoku solver
sudoku_solver: sudoku_solver.cpp
  $(CXX) $(CXXFLAGS) -o $@ $<

# Build the Sudoku maker
sudoku_maker: sudoku_maker.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Build the referee tool
referee: referee.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean binaries
clean:
	rm -f sudoku_solver sudoku_maker referee

.PHONY: all clean
