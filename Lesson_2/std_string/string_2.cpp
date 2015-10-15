#include <iostream>
#include <string>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: STD string 2");

  int big_value = 100500;
  std::string string_value = std::to_string(big_value);
  std::cout << string_value << std::endl;

  DBG("[Lesson 2]: STD string 2 [END]");
  return 0;
}

