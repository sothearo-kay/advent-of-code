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

  cout << validCount << endl;

  return 0;
}
