#include <algorithm>
#include <iostream>
#include <string>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: STD string: Solutions 2.1");
  
  // Trim whitespaces
  std::string str = "   Some leading and trailing whitespaces   Yeah   ";
  std::string whitespaces(" \t\f\v\n\r");
  size_t first = str.find_first_not_of(whitespaces);
  if (first != std::string::npos) {
    str.erase(0, first);
    size_t last = str.find_last_not_of(whitespaces);
    if (last != std::string::npos) {
      str.erase(last + 1);
    }
  } else {
    str.clear();  // str is all whitespace
  }
  // remove duplicated whitespaces
  std::string::iterator it = std::unique(str.begin(), str.end());
  str.resize(std::distance(str.begin(), it));
  std::cout << '[' << str << "]\n";

  DBG("[Lesson 2]: STD string: Solutions 2.1 [END]");
  return 0;
}

