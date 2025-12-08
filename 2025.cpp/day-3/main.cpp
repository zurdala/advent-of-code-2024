#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const string EXAMPLE_FILE = "example.txt";
const string INPUT_FILE = "input.txt";
const string FILE_TO_LOAD = INPUT_FILE;

ifstream loadInputFile(const string fileName) {
  ifstream inputFile{fileName};
  if (!inputFile) {
    cerr << "Could not open 'input.txt'\n";
    throw exception();
  } else {
    cout << "Reading file!\n";
  }
  return inputFile;
}

int c2i(const char c) { return c - '0'; }

int maxJoltagePart1(string line) {
    int maxNumberTens = c2i(line.at(0));
    int maxNumberUnits = c2i(line.at(1));
    for (int i = 2; i < line.length(); i++) {
      const int c = c2i(line.at(i));

      int currentMax = 10 * maxNumberTens + maxNumberUnits;
      const int candidate1 = 10 * maxNumberTens + c;
      const int candidate2 = 10 * maxNumberUnits + c;
      if (candidate1 > currentMax) {
          currentMax = candidate1;
      }
      if (candidate2 > currentMax) {
          currentMax = candidate2;
      }

      if (currentMax == candidate2) {
          maxNumberTens = maxNumberUnits;
          maxNumberUnits = c;
      }
      if (currentMax == candidate1) {
          maxNumberUnits = c;
      }
    }
    return maxNumberTens * 10 + maxNumberUnits;
}

int main() {
  ifstream inputFile = loadInputFile(FILE_TO_LOAD);

  int64_t result1{0};
  int64_t result2{0};

  string line;
  while (std::getline(inputFile, line)) {
    result1 += maxJoltagePart1(line);
  }

  cout << "Result Part 1 = " << result1 << endl;
  cout << "Result Part 2 = " << result2 << endl;

  return 0;
}
