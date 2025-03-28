#include <fstream>
#include <iostream>
#include <regex>
using namespace std;

int mul(int x, int y) { return x * y; }

int main() {
  fstream inFile("in.txt");
  string line;

  // Combined regex:
  //   - (mul\((\d+),(\d+)\)) matches "mul(x,y)" and captures x in group 2 and y
  //   in group 3.
  //   - (do\(\)) matches "do()".
  //   - (don't\(\)) matches "don't()".
  regex combinedPattern(R"((mul\((\d+),(\d+)\))|(do\(\))|(don't\(\)))");

  int sum = 0;
  bool isMulEnabled = true;

  while (getline(inFile, line)) {
    sregex_iterator it(line.begin(), line.end(), combinedPattern);
    sregex_iterator regEnd;

    while (it != regEnd) {
      string matchStr = it->str();

      if (matchStr.find("mul") == 0) {
        if (isMulEnabled) {
          int x = stoi((*it)[2].str());
          int y = stoi((*it)[3].str());
          sum += mul(x, y);
        }
      }

      else if (matchStr == "do()") {
        isMulEnabled = true;
      }

      else if (matchStr == "don't()") {
        isMulEnabled = false;
      }

      ++it;
    }
  }

  inFile.close();

  cout << sum << endl;

  // ---- Part 1
  /*
     For example, consider the following section of corrupted memory:

     xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))

     Only the four highlighted sections are real mul instructions. Adding up the
     result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).
  */

  // ---- Part 2
  /*
     Only the most recent do() or don't() instruction applies. At the beginning
     of the program, mul instructions are enabled.

     xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))

     This corrupted memory is similar to the example from before, but this time
     the mul(5,5) and mul(11,8) instructions are disabled because there is a
     don't() instruction before them. The other mul instructions function
     normally, including the one at the end that gets re-enabled by a do()
     instruction.

     This time, the sum of the results is 48 (2*4 + 8*5).
  */

  return 0;
}
