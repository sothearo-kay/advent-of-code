#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

bool isSafeReport(const vector<int> &levels) {
  // Single level is awalys true
  if (levels.size() < 2)
    return true;

  bool increasing = levels[1] > levels[0];
  for (size_t i = 1; i < levels.size(); ++i) {
    int diff = levels[i] - levels[i - 1];

    // Check if invalid difference
    if (diff == 0 || abs(diff) > 3)
      return false;

    // Check if direction changes
    if ((increasing && diff < 0) || (!increasing && diff > 0))
      return false;
  }

  return true;
}

bool isSafeWithOneRemoval(vector<int> &levels) {
  if (isSafeReport(levels))
    return true;

  // Try removing each level and check if it becomes safe
  for (size_t i = 0; i < levels.size(); ++i) {
    int removeElement = levels[i];

    levels.erase(levels.begin() + i);

    if (isSafeReport(levels)) {
      return true;
    }

    levels.insert(levels.begin() + i, removeElement);
  }

  return false;
}

int main() {
  ifstream inFile("in.txt");

  vector<vector<int>> reports;
  string line;

  while (getline(inFile, line)) {
    stringstream ss(line);
    vector<int> report;
    int num;

    while (ss >> num) {
      report.push_back(num);
    }

    if (!report.empty()) {
      reports.push_back(report);
    }
  }

  int count = 0;

  // ---- Part 1
  /*
     The engineers are trying to figure out which reports are safe. The
     Red-Nosed reactor safety systems can only tolerate levels that are either
     gradually increasing or gradually decreasing. So, a report only counts as
     safe if both of the following are true:

     - The levels are either all increasing or all decreasing.
     - Any two adjacent levels differ by at least one and at most three.
  */

  for (const auto &report : reports) {
    if (isSafeReport(report)) {
      count++;
    }
  }

  // ---- Part 2
  /*
     Now, the same rules apply as before, except if removing a single level from
     an unsafe report would make it safe, the report instead counts as safe.
  */

  for (const auto &report : reports) {
    if (isSafeWithOneRemoval(report)) {
      count++;
    }
  }

  // cout << count << endl;

  inFile.close();

  return 0;
}
