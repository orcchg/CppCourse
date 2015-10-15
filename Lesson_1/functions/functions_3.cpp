#include <cstdlib>
#include "logger.h"

void print(int value) {
  INF("Print: %i", value);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 3");

  if (argc < 2) {
    ERR("Invalid number of input parameters!");
    return 1;
  }

  int value = std::atoi(argv[1]);
  print(value);
  INF("Value: %i", value);

  DBG("[Lesson 1]: Functions 3 [END]");
  return 0;
}

