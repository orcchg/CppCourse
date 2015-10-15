#include <cstdio>
#include "logger.h"

void add(int value, int& destination) {
  destination += value;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers 3");

  int lhs = 0, rhs = 0;
  scanf("%i %i", &lhs, &rhs);

  add(lhs, rhs);
  INF("Value: %i", rhs);

  DBG("[Lesson 1]: Pointers 3 [END]");
  return 0;
}

