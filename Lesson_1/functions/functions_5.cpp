#include "logger.h"

int add(int source, int value) {
  return source + value;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 5");

  int result = add(2, 3);
  INF("Result: %i", result);

  DBG("[Lesson 1]: Functions 5 [END]");
  return 0;
}

