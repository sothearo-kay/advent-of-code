#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// Define a struct to hold each entry
struct PasswordEntry {
  int min;
  int max;
  char letter;
  string password;
};

vector<PasswordEntry> readPasswordEntries(const string &fileName) {
  vector<PasswordEntry> entries;
  fstream inFile(fileName);
  string line;

  while (getline(inFile, line)) {
    stringstream ss(line);
    int min, max;
    char letter;
    string password;

    ss >> min;         // Read min
    ss.ignore(1, '-'); // ignore '-'
    ss >> max;         // Read max;
    ss >> letter;      // Read character
    ss.ignore(1, ':'); // Ignore the ':'
    ss >> password;    // Read password

    entries.push_back({min, max, letter, password});
  }

  inFile.close();

  return entries;
}

int main() {
  vector<PasswordEntry> entries = readPasswordEntries("in.txt");

  int validCount = 0;

  // ---- Part 1
  /*
     For example, suppose you have the following list:

     0-3 a: abcde
     1-3 b: cdefg
     2-9 c: ccccccccc

     Each line gives the password policy and then the password. The password
     policy indicates the lowest and highest number of times a given letter must
     appear for the password to be valid. For example, 1-3 a means that the
     password must contain a at least 1 time and at most 3 times.
  */

  for (const auto &entry : entries) {
    int occurrences =
        count(entry.password.begin(), entry.password.end(), entry.letter);

    if (occurrences >= entry.min && occurrences <= entry.max) {
      validCount++;
    }
  }

  // ---- Part 2
  /*
     Each policy actually describes two positions in the password, where 1 means
     the first character, 2 means the second character, and so on. (Be careful;
     Toboggan Corporate Policies have no concept of "index zero"!) Exactly one
     of these positions must contain the given letter. Other occurrences of the
     letter are irrelevant for the purposes of policy enforcement.

     Given the same example list from above:

     - 1-3 a: abcde is valid: position 1 contains a and position 3 does not.
     - 1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
     - 2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
    */

  for (const auto &entry : entries) {
    bool firstPos = entry.password[entry.min - 1] == entry.letter;
    bool secondPos = entry.password[entry.max - 1] == entry.letter;

    // XOR ensures exactly one of them is true
    if (firstPos ^ secondPos) {
      validCount++;
    }
  }

  // cout << validCount << endl;

  return 0;
}
