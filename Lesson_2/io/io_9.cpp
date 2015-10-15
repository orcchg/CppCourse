#include <iostream>
#include "logger.h"

#define SIZE 24

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 9");

  int a = 0, b = 0;
  std::cin >> a >> b;
  std::cout << "a + b = " << a + b << std::endl;

  DBG("[Lesson 2]: IO 9 [END]");
  return 0;
}

