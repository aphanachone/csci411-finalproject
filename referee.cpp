// referee.cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Read an N×N block from stdin.
// Skips empty lines. Expects the first non-empty line to determine N.
vector<vector<int>> readBlock() {
    vector<vector<int>> grid;
    string line;
    // read first non-empty line
    while (getline(cin, line)) {
        if (line.find_first_not_of(" \t\r\n") != string::npos) {
            istringstream iss(line);
            vector<int> row;
            int x;
            while (iss >> x) row.push_back(x);
            if (!row.empty()) {
                grid.push_back(row);
                break;
            }
        }
    }
    if (grid.empty()) {
        cerr << "No input for block.\n";
        exit(1);
    }
    int N = grid[0].size();
    // read remaining rows
    while ((int)grid.size() < N && getline(cin, line)) {
        if (line.find_first_not_of(" \t\r\n") == string::npos) continue;
        istringstream iss(line);
        vector<int> row;
        int x;
        while (iss >> x) row.push_back(x);
        if ((int)row.size() != N) {
            cerr << "Each row must have " << N << " numbers.\n";
            exit(1);
        }
        grid.push_back(row);
    }
    if ((int)grid.size() != N) {
        cerr << "Expected " << N << " rows, got " << grid.size() << ".\n";
        exit(1);
    }
    return grid;
}

// Check if a vector of N ints contains exactly 1..N
bool is1toN(const vector<int>& v) {
    int N = v.size();
    unordered_set<int> seen(v.begin(), v.end());
    if ((int)seen.size() != N) return false;
    for (int i = 1; i <= N; i++)
        if (!seen.count(i)) return false;
    return true;
}

// Validate a completed N×N Sudoku
bool validateSudoku(const vector<vector<int>>& g) {
    int N = g.size();
    // check square
    for (auto &row : g) if ((int)row.size() != N) return false;
    // perfect‐square check
    int k = int(floor(sqrt(N) + 0.5));
    if (k*k != N) return false;
    // rows
    for (auto &row : g) if (!is1toN(row)) return false;
    // cols
    for (int c = 0; c < N; c++) {
        vector<int> col(N);
        for (int r = 0; r < N; r++) col[r] = g[r][c];
        if (!is1toN(col)) return false;
    }
    // boxes
    for (int br = 0; br < N; br += k) {
        for (int bc = 0; bc < N; bc += k) {
            vector<int> box;
            for (int r = br; r < br+k; r++)
                for (int c = bc; c < bc+k; c++)
                    box.push_back(g[r][c]);
            if (!is1toN(box)) return false;
        }
    }
    return true;
}

int main() {
    cout << "Mode (confirm/compare): ";
    string mode;
    if (!getline(cin, mode)) return 1;
    // lowercase
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if (mode == "confirm") {
        cout << "Enter Sudoku block:\n";
        auto grid = readBlock();
        if (validateSudoku(grid))
            cout << "Valid Sudoku.\n";
        else
            cout << "Invalid Sudoku.\n";
    }
    else if (mode == "compare") {
        cout << "Enter first Sudoku block:\n";
        auto a = readBlock();
        cout << "Enter second Sudoku block:\n";
        auto b = readBlock();
        if (a.size() != b.size()) {
            cout << "Blocks differ in size.\n";
            return 0;
        }
        int N = a.size();
        bool anyDiff = false;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (a[r][c] != b[r][c]) {
                    cout << "Difference at row " << r+1
                         << ", col " << c+1
                         << ": " << a[r][c]
                         << " vs " << b[r][c] << "\n";
                    anyDiff = true;
                }
            }
        }
        if (!anyDiff)
            cout << "No differences; blocks are identical.\n";
    }
    else {
        cout << "Unknown mode. Use \"confirm\" or \"compare\".\n";
        return 1;
    }

    return 0;
}
