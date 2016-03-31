#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO: Solutions 3");

  std::string input;
  std::getline(std::cin, input);
  
  std::fstream fs;
  fs.open("somefile_3.txt", std::fstream::out);
  std::copy(input.begin(), input.end(), std::ostream_iterator<char>(fs, ""));
  fs.close();

  DBG("[Lesson 2]: IO: Solutions 3 [END]");
  return 0;
}
