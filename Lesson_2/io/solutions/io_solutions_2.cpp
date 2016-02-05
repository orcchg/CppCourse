#include <iostream>
#include <fstream>
#include <string>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO: Solutions 2");

  std::string input;
  std::getline(std::cin, input);
  
  std::fstream fs;
  fs.open("somefile_2.txt", std::fstream::out);
  fs << input;
  fs.close();

  DBG("[Lesson 2]: IO: Solutions 2 [END]");
  return 0;
}

