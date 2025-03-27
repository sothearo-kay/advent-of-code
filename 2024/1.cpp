#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  ifstream inFile("in.txt");

  vector<int> a, b;

  int x, y;
  while (inFile >> x >> y) {
    a.push_back(x);
    b.push_back(y);
  }

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  long long sum = 0;

  // ---- Part 1
  /*
     To find out, pair up the numbers and measure how far apart they are. Pair
     up the smallest number in the left list with the smallest number in the
     right list, then the second-smallest left number with the second-smallest
     right number, and so on.

     Within each pair, figure out how far apart the two numbers are; you'll need
     to add up all of those distances. For example, if you pair up a 3 from the
     left list with a 7 from the right list, the distance apart is 4; if you
     pair up a 9 with a 3, the distance apart is 6.
  */
  for (size_t i = 0; i < a.size(); ++i) {
    sum += abs(a[i] - b[i]);
  }

  // ---- Part 2
  /*
     This time, you'll need to figure out exactly how often each number from the
     left list appears in the right list. Calculate a total similarity score by
     adding up each number in the left list after multiplying it by the number
     of times that number appears in the right list.
  */

  // Count occurences of each number in b
  // This loop runs in O(n) time.
  unordered_map<int, int> freq;
  for (int num : b) {
    freq[num]++; // O(1) average time for unordered_map insert/update
  }

  // Compute the similarity score
  // This loop runs in O(n) time.
  for (int num : a) {
    sum += num * freq[num];
  }

  // Before optimization
  // It runs in O(n^2) time due to the nested loops.
  for (size_t i = 0; i < a.size(); ++i) {
    int count = 0;
    for (size_t j = 0; j < a.size(); ++j) {
      if (a[i] == b[j]) {
        count++;
      }
    }
    sum += a[i] * count;
  }

  // cout << sum << endl;

  inFile.close();

  return 0;
}
