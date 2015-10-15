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

struct Strategy {
  F method;
  const char* name;
};

namespace Factory {

Strategy create(int value) {
  Strategy strategy;

  switch (value) {
    default:
    case 0:
      strategy.method = arithmetic::add;
      strategy.name = "Add";
      break;
    case 1:
      strategy.method = arithmetic::sub;
      strategy.name = "Sub";
      break;
    case 2:
      strategy.method = arithmetic::mul;
      strategy.name = "Mul";
      break;
    case 3:
      strategy.method = arithmetic::div;
      strategy.name = "Div";
      break;
    case 4:
      strategy.method = arithmetic::res;
      strategy.name = "Res";
      break;
  }

  return strategy;
}

}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers 8");

  int lhs = 0, rhs = 0;
  scanf("%i %i", &lhs, &rhs);

  Strategy strategies[15];

  for (size_t i = 0; i < 15; ++i) {
    int random = std::rand() % 5;
    strategies[i] = Factory::create(random);
  }

  for (size_t i = 0; i < 15; ++i) {
    INF("Method: %s, Value: %i", strategies[i].name, evaluate(lhs, rhs, strategies[i].method));
  }

  DBG("[Lesson 1]: Pointers 8 [END]" );
  return 0;
}

