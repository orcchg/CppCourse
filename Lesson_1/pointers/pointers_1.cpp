#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers 1");

  int variable = 0;
  scanf("%i", &variable);
  INF("Value: %i", variable);

  DBG("[Lesson 1]: Pointers 1 [END]");
  return 0;
}

