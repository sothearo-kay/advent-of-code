#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

struct HashPair {
  size_t operator()(const pair<int, int> &p) const {
    return p.first * 31 + p.second;
  }
};

// ----------------------
// Part
// ----------------------

// Directions for checking the XMAS pattern (horizontal, vertical, and diagonal)
const int dxXMAS[] = {0, 0, 1, -1, 1, -1, 1, -1};
const int dyXMAS[] = {1, -1, 0, 0, 1, -1, -1, 1};

bool findXMAS(const vector<string> &grid, int x, int y, int dir,
              unordered_set<pair<int, int>, HashPair> &visited) {
  int rows = grid.size(), cols = grid[0].size();
  string word = "XMAS";
  for (int i = 0; i < 4; i++) {
    int nx = x + i * dxXMAS[dir];
    int ny = y + i * dyXMAS[dir];
    if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] != word[i])
      return false;
  }
  for (int i = 0; i < 4; i++) {
    int nx = x + i * dxXMAS[dir];
    int ny = y + i * dyXMAS[dir];
    visited.insert({nx, ny});
  }
  return true;
}

int countXMAS(const vector<string> &grid) {
  vector<pair<int, int>> xPositions;
  unordered_set<pair<int, int>, HashPair> visited;
  int rows = grid.size(), cols = grid[0].size();
  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == 'X') {
        xPositions.emplace_back(i, j);
      }
    }
  }
  for (auto [x, y] : xPositions) {
    if (visited.find({x, y}) != visited.end())
      continue;
    for (int d = 0; d < 8; d++) {
      if (findXMAS(grid, x, y, d, visited)) {
        count++;
      }
    }
  }
  return count;
}

// ----------------------
// Part 2: Revised X-MAS Pattern (X shape)
// ----------------------
// For an X-MAS occurrence, in a 3x3 block centered at (i, j):
//
//    [i-1][j-1]    [i-1][j+1]
//           (A)
//    [i+1][j-1]    [i+1][j+1]
//
// The pattern is valid if the center is 'A' and:
//    - One diagonal (top-left to bottom-right) is either "M A S" or "S A M"
//    - The other diagonal (top-right to bottom-left) is either "M A S" or "S A
//    M"
//
int countXMASX(const vector<string> &grid) {
  int count = 0;
  int rows = grid.size(), cols = grid[0].size();

  // Loop over cells that can be the center of a 3x3 block.
  for (int i = 1; i < rows - 1; i++) {
    for (int j = 1; j < cols - 1; j++) {
      if (grid[i][j] != 'A')
        continue;

      // Extract diagonal characters
      char topLeft = grid[i - 1][j - 1];
      char topRight = grid[i - 1][j + 1];
      char bottomLeft = grid[i + 1][j - 1];
      char bottomRight = grid[i + 1][j + 1];

      // For the diagonal from top-left to bottom-right:
      bool diag1Valid = ((topLeft == 'M' && bottomRight == 'S') ||
                         (topLeft == 'S' && bottomRight == 'M'));

      // For the diagonal from top-right to bottom-left:
      bool diag2Valid = ((topRight == 'M' && bottomLeft == 'S') ||
                         (topRight == 'S' && bottomLeft == 'M'));

      if (diag1Valid && diag2Valid)
        count++;
    }
  }
  return count;
}

int main() {
  ifstream inFile("in.txt");

  if (!inFile) {
    cerr << "Error opening file!" << endl;
    return 1;
  }

  vector<string> grid;
  string line;

  while (getline(inFile, line)) {
    grid.push_back(line);
  }

  inFile.close();

  int totalXMAS = countXMAS(grid);
  int totalXMASX = countXMASX(grid);

  cout << "Total XMAS occurrences: " << totalXMAS << endl;
  cout << "Total X-MAS (X pattern) occurrences: " << totalXMASX << endl;

  return 0;
}
