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

int main() {
  string fileName = "in.txt";
  InputData input = readInput(fileName);

  cout << "Rules:" << endl;
  for (const auto &rule : input.rules) {
    cout << rule.first << "|" << rule.second << endl;
  }

  cout << "\nNumber Lists:" << endl;
  for (const auto &list : input.numberLists) {
    for (int num : list) {
      cout << num << " ";
    }
    cout << endl;
  }

  return 0;
}
