#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const string INPUT_FILE = "input.txt";

string readIdsLine(const string fileName) {
  ifstream inputFile{fileName};
  if (!inputFile) {
    cerr << "Could not open 'input.txt'\n";
    throw exception();
  } else {
    cout << "Reading file!\n";
  }
  string line;
  getline(inputFile, line);
  return line;
}

vector<string> splitLine(const string longLine, char delim) {
  stringstream longStream{longLine};

  string part;
  vector<string> parts;

  while (getline(longStream, part, delim)) {
    parts.push_back(part);
  }
  return parts;
}

int64_t parseId(const string id) {
  int64_t idAsInt;
  sscanf(id.c_str(), "%ld", &idAsInt);
  return idAsInt;
}

vector<string> generateIdRange(string startIdRange, string endIdRange) {
  int64_t start = parseId(startIdRange);
  int64_t end = parseId(endIdRange);
  string id;
  vector<string> ids;
  for (int64_t i = start; i <= end; i++) {
    ids.push_back(to_string(i));
  }
  return ids;
}

void addIdToResult(int64_t id, int64_t &result, int part) {
  cout << "Adding to result " << part << " = " << id << endl;
  result = result + id;
}

bool isIdBadForPart1(const string id) {
  int32_t len = id.length();
  if (len % 2 != 0) {
    return false;
  }
  string part1 = id.substr(0, len / 2);
  string part2 = id.substr(len / 2, len / 2);
  return part1.compare(part2) == 0; // they are bad if they are equal
}

bool isPatternRepeated(const string id, const int len) {
  if (len > id.length() / 2) {
    throw std::exception();
  }

  int maxPairs = id.length() / len - 1;
  string partA;
  string partB;
  bool patternIsRepeated = true;

  for (int i = 0; i < maxPairs; i++) {
    partA = id.substr(i * len, len);
    partB = id.substr((i + 1) * len, len);
    patternIsRepeated = patternIsRepeated & (partA.compare(partB) == 0);
    if (!patternIsRepeated) {
      break;
    }
  }
  return patternIsRepeated;
}

bool isIdBadForPart2(const string id) {
  int32_t len = id.length();
  bool out = false;

  for (int32_t sublen = 1; sublen <= len / 2; sublen++) {
    // the different substrings need to fit
    if (len % sublen != 0) {
      continue;
    }

    out = isPatternRepeated(id, sublen);
    if (out) {
      return true;
    }
  }
  return false;
}

int main() {
  const string allInOneLine = readIdsLine(INPUT_FILE);
  int64_t result1{0};
  int64_t result2{0};

  vector<string> lines = splitLine(allInOneLine, ',');

  for (const string &line : lines) {
    // cout << line << endl;
    vector<string> idsRange = splitLine(line, '-');
    vector<string> ids = generateIdRange(idsRange[0], idsRange[1]);
    for (const string &id : ids) {
      if (isIdBadForPart1(id)) {
        addIdToResult(parseId(id), result1, 1);
      }
      if (isIdBadForPart2(id)) {
        addIdToResult(parseId(id), result2, 2);
      }
    }
  }

  cout << "Result Part 1 = " << result1 << endl;
  cout << "Result Part 2 = " << result2 << endl;

  return 0;
}
