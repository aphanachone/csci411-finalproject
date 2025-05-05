#!/usr/bin/env bash
EXEC=./sudoku_solver

for i in {01..05}; do
  printf "test_%s: " "$i"
  
  # run solver, capture both stdout and stderr
  "$EXEC" < test/test_"$i".in > actual_"$i".out 2>&1

  # compare against expected
  if diff -u test/test_"$i".out actual_"$i".out > /dev/null; then
    echo PASS
  else
    echo FAIL
  fi
done
