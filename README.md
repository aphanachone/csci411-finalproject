# csci411-finalproject

## Instructions


1. Run the make file
   
<code>make clean</code>

<code>make</code>

2. Make the testing script executable

<code>chmod +x run_tests.sh</code>

3. Run the tests

<code>./run_tests.sh</code>

---

This will test the five input files in /test/ and compare the actual outputs to the expected outputs.

The tests include a standard 9x9 board, 16x16 board, 25x25 board, and error handling for unsolvable and non-square boards.

---

## Included are files purely for curiosity and to confirm the validity of sudoku_solver.cpp, if needed.

### sudoku_maker.cpp

This allowed me to create a sudoku boards of 9x9, 16x16, 25x25, 36x36, and upto 100x100. N must be a squarable value.

It will ask for the desired N and the amount of empty cells. It empties cells at random so the larger the boards get, the more unsure it is if it will be possible to solve them.

To best create a board with only one solution, it is recommended to have a maximum of 40% as empty.

It then outputs the puzzle in a format that sudoku_solver accepts and the desired solution.

### referee.cpp

This file allows us to confirm if a solved sudoku board is valid and compare the solutions of sudoku_maker with the output of sudoku_solver.
