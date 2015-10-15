#include <iostream>
#include <fstream>
#include <string>
#include "logger.h"

#define SIZE 24

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 10");

  std::string line;

  std::fstream fs;
  fs.open("io_10.cpp", std::fstream::in);

  while (std::getline(fs, line)) {
    std::cout << line << std::endl;
  }

  fs.close();

  DBG("[Lesson 2]: IO 10 [END]");
  return 0;
}

