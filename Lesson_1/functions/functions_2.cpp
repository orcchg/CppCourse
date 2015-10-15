#include "logger.h"

void print(const char* string) {
  INF("Print: %s", string);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 2");

  if (argc < 2) {
    ERR("Invalid number of input parameters!");
    return 1;
  }
  print(argv[1]);

  DBG("[Lesson 1]: Functions 2 [END]");
  return 0;
}

