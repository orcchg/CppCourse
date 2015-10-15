#include <iostream>
#include <string>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: STD string 1");

  std::string str;
  std::getline(std::cin, str);
  std::cout << str << std::endl;

  DBG("[Lesson 2]: STD string 1 [END]");
  return 0;
}

