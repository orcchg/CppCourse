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

namespace Factory {

F create(int value) {
  switch (value) {
    default:
    case 0: return arithmetic::add;
    case 1: return arithmetic::sub;
    case 2: return arithmetic::mul;
    case 3: return arithmetic::div;
    case 4: return arithmetic::res;
  }
}

}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers 7");

  int lhs = 0, rhs = 0;
  scanf("%i %i", &lhs, &rhs);

  F strategies[15];

  for (size_t i = 0; i < 15; ++i) {
    int random = std::rand() % 5;
    strategies[i] = Factory::create(random);
  }

  for (size_t i = 0; i < 15; ++i) {
    INF("Value: %i", evaluate(lhs, rhs, strategies[i]));
  }

  DBG("[Lesson 1]: Pointers 7 [END]");
  return 0;
}

