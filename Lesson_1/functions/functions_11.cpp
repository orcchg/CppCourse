#include "logger.h"

int factorial(int N) {
  if (N == 0) {
    return 1;
  }
  return N * factorial(N - 1);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 11");
  INF("Result: %i", factorial(8));
  DBG("[Lesson 1]: Functions 11 [END]");
  return 0;
}

