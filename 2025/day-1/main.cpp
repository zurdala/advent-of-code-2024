#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

const std::string INPUT_FILE = "input.txt";

int wrapCounter(int counter) {
  if (counter < 0) {
    counter = 100 - (abs(counter) % 100);
  }
  if (counter > 99) {
    counter = counter % 100;
  }

  return counter;
}

struct Instruction {
  int dir;
  int steps;
};

Instruction processLine(const std::string line) {
  Instruction instruction;
  char letter;
  std::sscanf(line.c_str(), "%c%3i", &letter, &instruction.steps);
  if (letter == 'R') {
    instruction.dir = +1;
  } else {
    instruction.dir = -1;
  }
  return instruction;
}

int updateCounter(const int counter, const Instruction inst) {
  return counter + inst.dir * inst.steps;
}

int buildPasswordPart1(int password, const int counter) {
  if (counter == 0) {
    ++password;
  }
  return password;
}

int buildPasswordPart2(int password, const int counter,
                       const Instruction inst) {
  // if (counter == 0) {
  //   ++password;
  // }
  int crossingsOnZero{0};
  int c = counter;

  for (int i = 0; i < inst.steps; ++i) {
    c = c + inst.dir;
    c = wrapCounter(c);
    if (c == 0) {
      ++crossingsOnZero;
    }
  }
  return password + crossingsOnZero;

  // if (inst.dir > 0) {
  //     crossingsOnZero += inst.steps / 100;
  //     if (counter + (inst.steps % 100) > 99) {
  //         ++crossingsOnZero;
  //     }
  // } else if (inst.dir  < 0) {
  //     if (counter - (inst.steps % 100) < 0 ) {
  //         ++crossingsOnZero;
  //     }
  //     crossingsOnZero += inst.steps / 100;
  // } else {
  //     std::cout << "---- Nothing to do -----";
  // }
  // password += crossingsOnZero;
  // return password;
}

int main() {
  int counter{50};
  int password1{0};
  int password2{0};

  std::ifstream inputFile{INPUT_FILE};
  if (!inputFile) {
    std::cerr << "Could not open 'input.txt'\n";
    return 1;
  } else {
    std::cout << "Reading file!\n";
  }

  std::string line;
  Instruction inst;
  int i{0};
  while (std::getline(inputFile, line)) {
    inst = processLine(line);
    password2 = buildPasswordPart2(password2, counter, inst);
    counter = wrapCounter(updateCounter(counter, inst));
    password1 = buildPasswordPart1(password1, counter);
    std::cout << "processing line " << i << ", (" << line << ")"
              << ", dir*steps = " << inst.dir * inst.steps
              << ", counter = " << counter << ", password1 = " << password1
              << ", password2 = " << password2 << std::endl;
    ++i;
  }
  inputFile.close();

  std::cout << "\n\nPassword 1 is " << password1 << std::endl;
  std::cout << "\n\nPassword 2 is " << password2 << std::endl;

  return 0;
}
