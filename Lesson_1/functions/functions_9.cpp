#include "logger.h"

void add(int& source, int value) {
  source += value;
  INF("Source: %i", source);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 9");

  int source = 2;
  add(source, 3);
  INF("Result: %i", source);

  DBG("[Lesson 1]: Functions 9 [END]");
  return 0;
}

