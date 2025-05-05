// sudoku_maker.cpp
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

// Fills an N×N grid (N=k²) with a valid Sudoku solution via pattern+shuffle
vector<vector<int>> generateFullSolution(int N) {
    int k = int(sqrt(N));
    vector<vector<int>> g(N, vector<int>(N));

    // 1) Base arithmetic pattern (values 0..N-1)
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            g[r][c] = (k*(r % k) + r/k + c) % N;

    random_device rd;
    mt19937 rng(rd());

    // 2) Shuffle symbol mapping
    vector<int> sym(N);
    iota(sym.begin(), sym.end(), 0);
    shuffle(sym.begin(), sym.end(), rng);
    for (int r = 0; r < N; r++)
      for (int c = 0; c < N; c++)
        g[r][c] = sym[g[r][c]];

    // Helper to shuffle rows within bands, then shuffle the bands
    auto shuffleBands = [&](vector<vector<int>>& grid){
      // rows in each band
      for (int band = 0; band < k; band++) {
        vector<int> rows(k);
        iota(rows.begin(), rows.end(), band*k);
        shuffle(rows.begin(), rows.end(), rng);
        vector<vector<int>> copy = grid;
        for (int i = 0; i < k; i++)
          grid[band*k + i] = copy[rows[i]];
      }
      // shuffle the bands themselves
      vector<int> bands(k);
      iota(bands.begin(), bands.end(), 0);
      shuffle(bands.begin(), bands.end(), rng);
      vector<vector<int>> copy = grid;
      for (int i = 0; i < k; i++)
        for (int r = 0; r < k; r++)
          grid[i*k + r] = copy[bands[i]*k + r];
    };

    // 3) Shuffle rows/bands
    shuffleBands(g);

    // 4) Transpose → shuffle rows/bands → transpose back (to handle columns)
    vector<vector<int>> t(N, vector<int>(N));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        t[i][j] = g[j][i];

    shuffleBands(t);

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        g[j][i] = t[i][j];

    // convert 0..N-1 → 1..N
    for (int r = 0; r < N; r++)
      for (int c = 0; c < N; c++)
        g[r][c] += 1;

    return g;
}

int main() {
    int N, BLANKS;
    cout << "Enter N (perfect square, e.g. 9,16,25...): ";
    if (!(cin >> N) || N <= 0) return 1;
    int k = int(floor(sqrt(N) + 0.5));
    if (k*k != N) {
        cerr << "Error: N must be a perfect square.\n";
        return 1;
    }

    cout << "Enter number of blanks (0.." << N*N << "): ";
    if (!(cin >> BLANKS) || BLANKS < 0 || BLANKS > N*N) return 1;

    // Generate and punch holes
    auto full   = generateFullSolution(N);
    vector<int> idx(N*N);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end(), mt19937(random_device{}()));

    auto puzzle = full;
    for (int i = 0; i < BLANKS; i++) {
        puzzle[idx[i]/N][idx[i]%N] = 0;
    }

    // Output
    cout << "\nFULL SOLUTION:\n";
    for (auto &row : full) {
        for (int v : row) cout << v << ' ';
        cout << '\n';
    }
    cout << "\nPUZZLE:\n";
    for (auto &row : puzzle) {
        for (int v : row) cout << v << ' ';
        cout << '\n';
    }
    return 0;
}