#include <cstdlib>
#include "logger.h"

int value = 100;  // global variable

void print(int value) {
  INF("Print: %i", value);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 4");

  if (argc < 2) {
    ERR("Invalid number of input parameters!");
    return 1;
  }

  int value = std::atoi(argv[1]);
  print(value);
  INF("Value: %i", value);

  DBG("[Lesson 1]: Functions 4 [END]");
  return 0;
}

