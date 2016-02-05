#include <iostream>
#include <fstream>
#include <string>
#include "logger.h"

void input(const std::string& filename) {
  std::string line;

  std::fstream fs;
  fs.open(filename, std::fstream::in);

  while (std::getline(fs, line)) {
    std::cout << line << std::endl;
  }

  fs.close();
}

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO: Solutions 1");
  input("../expressions.txt");
  DBG("[Lesson 2]: IO: Solutions 1 [END]");
  return 0;
}

