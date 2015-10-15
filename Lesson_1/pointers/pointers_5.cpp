#include <cstdio>
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

int evaluate(int lhs, int rhs, int function(int, int)) {
  return function(lhs, rhs);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers 5");

  int lhs = 0, rhs = 0;
  scanf("%i %i", &lhs, &rhs);

  INF("Add: %i", evaluate(lhs, rhs, arithmetic::add));
  INF("Sub: %i", evaluate(lhs, rhs, arithmetic::sub));
  INF("Mul: %i", evaluate(lhs, rhs, arithmetic::mul));
  INF("Div: %i", evaluate(lhs, rhs, arithmetic::div));
  INF("Res: %i", evaluate(lhs, rhs, arithmetic::res));

  DBG("[Lesson 1]: Pointers 5 [END]");
  return 0;
}

