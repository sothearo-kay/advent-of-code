#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
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

// Fixes an invalid list by reordering it to satisfy the rules.
/*
   The approach:
   - Create a set of nodes (pages) from the list.
   - Build a graph for rules that apply (only if both A and B are present).
   - Topologically sort the constrained numbers (using a min-heap for
   stability).
   - Then sort the original list based on this order.
*/
vector<int> fixList(const vector<int> &list,
                    const vector<pair<int, int>> &rules) {
  unordered_set<int> nodes(list.begin(), list.end());
  unordered_map<int, vector<int>> graph;
  unordered_map<int, int> inDegree;

  // Initialize in-degree for each node.
  for (int node : nodes) {
    inDegree[node] = 0;
  }

  // Build graph edges for each rule (if both numbers appear in the list).
  for (const auto &rule : rules) {
    int A = rule.first, B = rule.second;
    if (nodes.count(A) && nodes.count(B)) {
      graph[A].push_back(B);
      inDegree[B]++;
    }
  }

  // Use a min-heap for nodes with in-degree 0 to achieve a stable order.
  priority_queue<int, vector<int>, greater<int>> pq;
  for (const auto &entry : inDegree) {
    if (entry.second == 0)
      pq.push(entry.first);
  }

  vector<int> sorted;
  while (!pq.empty()) {
    int node = pq.top();
    pq.pop();
    sorted.push_back(node);
    for (int neighbor : graph[node]) {
      inDegree[neighbor]--;
      if (inDegree[neighbor] == 0)
        pq.push(neighbor);
    }
  }

  // If some nodes weren't included (due to cycles or disconnected parts)
  // add them.
  if (sorted.size() < nodes.size()) {
    for (int node : nodes) {
      if (find(sorted.begin(), sorted.end(), node) == sorted.end())
        sorted.push_back(node);
    }
  }

  // Create a ranking map from the topologically sorted order.
  unordered_map<int, int> order;
  for (int i = 0; i < sorted.size(); i++) {
    order[sorted[i]] = i;
  }

  // Sort the original list based on the computed order.
  // For numbers not in the ranking, assign a very high rank.
  vector<int> fixedList = list;
  sort(fixedList.begin(), fixedList.end(), [&](int a, int b) {
    int rankA = order.count(a) ? order[a] : 1000000;
    int rankB = order.count(b) ? order[b] : 1000000;
    return rankA < rankB;
  });

  return fixedList;
}

int main() {
  string fileName = "in.txt";
  InputData input = readInput(fileName);

  // --- Part 1
  int sumMiddleValues = 0;

  for (const auto &list : input.numberLists) {
    bool valid = checkRules(list, input.rules);

    if (valid && !list.empty()) {
      int middleIndex = (list.size() - 1) / 2;
      sumMiddleValues += list[middleIndex];
    }
  }

  // -- Part 2
  int sumMiddleValuesOfInvalid = 0;

  for (const auto &list : input.numberLists) {
    bool valid = checkRules(list, input.rules);

    if (!valid) {
      vector<int> fixedList = fixList(list, input.rules);
      int middleIndex = (fixedList.size() - 1) / 2;
      sumMiddleValuesOfInvalid += fixedList[middleIndex];
    }
  }

  cout << "Sum of middle elements of valid lists: " << sumMiddleValues << endl;
  cout << "Sum of middle elements of fixed (invalid) lists: "
       << sumMiddleValuesOfInvalid << endl;

  return 0;
}
