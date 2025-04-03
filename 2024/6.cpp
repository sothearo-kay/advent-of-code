#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// Define a state as a tuple: (row, col, direction)
// Directions: 0 = up, 1 = right, 2 = down, 3 = left
typedef tuple<int, int, int> State;

// Returns true if (r, c) is within grid bounds.
bool inBounds(int r, int c, int rows, int cols) {
  return (r >= 0 && r < rows && c >= 0 && c < cols);
}

// Given a direction, return the delta row and delta col for moving forward.
pair<int, int> moveDelta(int dir) {
  switch (dir) {
  case 0:
    return {-1, 0}; // up
  case 1:
    return {0, 1}; // right
  case 2:
    return {1, 0}; // down
  case 3:
    return {0, -1}; // left
  }
  return {0, 0}; // default (should never reach here)
}

// Map a character to initial direction.
int charToDir(char ch) {
  if (ch == '^')
    return 0;
  if (ch == '>')
    return 1;
  if (ch == 'v')
    return 2;
  if (ch == '<')
    return 3;
  return 0; // default
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

  int rows = grid.size();
  if (rows == 0)
    return 0;
  int cols = grid[0].size();

  // Find the guard's starting position and orientation.
  int startR = -1, startC = -1, startDir = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      char ch = grid[i][j];
      if (ch == '^' || ch == 'v' || ch == '<' || ch == '>') {
        startR = i;
        startC = j;
        startDir = charToDir(ch);
        break;
      }
    }
    if (startR != -1)
      break;
  }

  if (startR == -1) {
    cerr << "Guard starting position not found!" << endl;
    return 1;
  }

  // Remove the guard symbol from the grid (set to '.') so it acts like an empty
  // cell.
  grid[startR][startC] = '.';

  // Set to store distinct positions visited (only position, not orientation)
  set<pair<int, int>> visitedPositions;

  // Initialize guard state.
  int r = startR, c = startC, dir = startDir;
  visitedPositions.insert({r, c});

  while (true) {
    // Determine the cell in front.
    auto [dr, dc] = moveDelta(dir);
    int nr = r + dr, nc = c + dc;

    // If the next cell is out-of-bounds, the guard leaves the mapped area.
    if (!inBounds(nr, nc, rows, cols)) {
      break;
    }

    // If there is an obstruction (a '#' character) in front, turn right.
    if (grid[nr][nc] == '#') {
      dir = (dir + 1) % 4;
    } else {
      // Otherwise, move forward.
      r = nr;
      c = nc;
      visitedPositions.insert({r, c});
    }
  }

  // Output the number of distinct positions visited.
  cout << "Distinct positions visited: " << visitedPositions.size() << endl;
  return 0;
}
