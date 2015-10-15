#include <cstdio>
#include "logger.h"

int division(int numerator, int denominator, int* residual) {
  int quotient = numerator / denominator;
  *residual = numerator % denominator;
  return quotient;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers 4");

  int lhs = 0, rhs = 0;
  scanf("%i %i", &lhs, &rhs);

  int residual = 0;
  int quotient = division(lhs, rhs, &residual);
  INF("Quotient: %i, Residual: %i", quotient, residual);

  DBG("[Lesson 1]: Pointers 4 [END]");
  return 0;
}

