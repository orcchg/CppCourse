#include "logger.h"

void add(int source, int value) {
  source += value;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 6");

  int source = 2;
  add(source, 3);
  INF("Result: %i", source);

  DBG("[Lesson 1]: Functions 6 [END]");
  return 0;
}

