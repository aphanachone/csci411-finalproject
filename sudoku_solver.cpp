#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

// Return true if placing 'candidate' at grid[row][col] violates no constraints
bool isValidPlacement(const vector<vector<int>>& grid, int row, int col, int candidate) {
    int size = grid.size();
    int region = static_cast<int>(std::sqrt(size));

    // Check row & column
    for (int i = 0; i < size; i++) {
        if (grid[row][i] == candidate || grid[i][col] == candidate) {
            return false;
        }
    }

    // Determine box start
    int boxRow = (row / region) * region;
    int boxCol = (col / region) * region;

    // Check region
    for (int r = boxRow; r < boxRow + region; r++) {
        for (int c = boxCol; c < boxCol + region; c++) {
            if (grid[r][c] == candidate) {
                return false;
            }
        }
    }
    return true;
}

// Recursive brute-force backtracking
bool solveSudoku(vector<vector<int>>& grid, int cellIndex = 0) {
    int size = grid.size();
    // All cells filled?
    if (cellIndex == size * size) {
        return true;
    }
    int row = cellIndex / size;
    int col = cellIndex % size;
    // Skip non-zero cells
    if (grid[row][col] != 0) {
        return solveSudoku(grid, cellIndex + 1);
    }
    // Try each value
    for (int val = 1; val <= size; val++) {
        if (isValidPlacement(grid, row, col, val)) {
            grid[row][col] = val;

            if (solveSudoku(grid, cellIndex + 1)) {
                return true;
            }

            // Undo
            grid[row][col] = 0;
        }
    }
    // No valid assignment, backtrack
    return false;
}

int main() {
    vector<vector<int>> grid;
    string inputLine;

    // Read first non-empty line to detect N
    while (getline(cin, inputLine)) {
        if (inputLine.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }

        istringstream rowStream(inputLine);
        vector<int> rowData;
        int cellValue;

        while (rowStream >> cellValue) {
            rowData.push_back(cellValue);
        }

        if (!rowData.empty()) {
            grid.push_back(rowData);
            break;
        }
    }
    if (grid.empty()) {
        cerr << "No input provided.\n";
        return 1;
    }
    int N = grid[0].size();
    // Read the remaining N-1 rows
    while (static_cast<int>(grid.size()) < N && getline(cin, inputLine)) {
        if (inputLine.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }
        istringstream rowStream(inputLine);
        vector<int> rowData;
        int cellValue;
        while (rowStream >> cellValue) {
            rowData.push_back(cellValue);
        }
        if (static_cast<int>(rowData.size()) != N) {
            cerr << "Error: each row must have " << N << " numbers.\n";
            return 1;
        }
        grid.push_back(rowData);
    }
    if (static_cast<int>(grid.size()) != N) {
        cerr << "Error: expected " << N << " rows, but got " << grid.size() << ".\n";
        return 1;
    }

    // Solve and print solution
    if (solveSudoku(grid)) {
        cout << "Solution:\n";
        for (const auto& row : grid) {
            for (int val : row) {
                cout << val << ' ';
            }
            cout << '\n';
        }
    }
    else {
        cout << "No solution exists.\n";
    }
    return 0;
}