#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct InputData {
  vector<pair<int, int>> rules;
  vector<vector<int>> numberLists;
};

InputData readInput(const string &fileName) {
  ifstream inFile(fileName);
  if (!inFile.is_open()) {
    cerr << "Error: The input file '" << fileName << "' was not found." << endl;
    exit(1);
  }

  InputData data;
  string line;
  bool readingRules = true; // Start reading rules first

  while (getline(inFile, line)) {
    // Empty line indicates the end of the rules section.
    if (line.empty()) {
      readingRules = false;
      continue;
    }

    if (readingRules) {
      // Each rule line is in the format "A|B"
      stringstream ss(line);
      int a, b;
      char sep;

      if (ss >> a >> sep >> b && sep == '|') {
        data.rules.emplace_back(a, b);
      }
    } else {
      // Process lines containing comma-separated numbers.
      vector<int> numbers;
      stringstream ss(line);
      int num;
      char comma;

      while (ss >> num) {
        numbers.push_back(num);
        ss >> comma; // Skip the comma if present
      }

      if (!numbers.empty()) {
        data.numberLists.push_back(numbers);
      }
    }
  }

  inFile.close();

  return data;
}

// This function checks if a given list of numbers satisfies all the rules.
// For each rule (A, B), we find A and B and ensure A comes before B.
bool checkRules(const vector<int> &list, const vector<pair<int, int>> rules) {
  for (const auto &rule : rules) {
    int A = rule.first;
    int B = rule.second;

    // Find positions of A and B in the list
    auto itA = find(list.begin(), list.end(), A);
    auto itB = find(list.begin(), list.end(), B);

    // Only if both are present do we check their order
    if (itA != list.end() && itB != list.end() && itA >= itB) {
      return false;
    }
  }

  return true;
}

int main() {
  string fileName = "in.txt";
  InputData input = readInput(fileName);

  int listIndex = 1;
  int sumMiddleValues = 0;

  for (const auto &list : input.numberLists) {
    bool valid = checkRules(list, input.rules);

    if (valid && !list.empty()) {
      int middleIndex = (list.size() - 1) / 2;
      sumMiddleValues += list[middleIndex];
    }
  }

  cout << "Sum of middle elements of valid lists: " << sumMiddleValues << endl;

  return 0;
}
