#include <cstdio>
#include <cstdlib>
#include "logger.h"

namespace arithmetic {

int add(int lhs, int rhs) {
  return lhs + rhs;
}

int sub(int lhs, int rhs) {
  return lhs - rhs;
}

int mul(int lhs, int rhs) {
  return lhs * rhs;
}

int div(int lhs, int rhs) {
  return lhs / rhs;
}

int res(int lhs, int rhs) {
  return lhs % rhs;
}

}

typedef int (*F)(int, int);

int evaluate(int lhs, int rhs, F function) {
  return function(lhs, rhs);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers 6");

  int lhs = 0, rhs = 0;
  scanf("%i %i", &lhs, &rhs);

  F strategies[15];

  for (size_t i = 0; i < 15; ++i) {
    int random = std::rand() % 5;
    switch (random) {
      case 0: strategies[i] = arithmetic::add; break;
      case 1: strategies[i] = arithmetic::sub; break;
      case 2: strategies[i] = arithmetic::mul; break;
      case 3: strategies[i] = arithmetic::div; break;
      case 4: strategies[i] = arithmetic::res; break;
    }
  }

  for (size_t i = 0; i < 15; ++i) {
    INF("Value: %i", evaluate(lhs, rhs, strategies[i]));
  }

  DBG("[Lesson 1]: Pointers 6 [END]");
  return 0;
}

