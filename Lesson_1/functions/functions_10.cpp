#include "logger.h"

int fibonacci(int N) {
  if (N == 0 || N == 1) {
    return 1;
  }
  return fibonacci(N - 1) + fibonacci(N - 2);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 10");
  INF("Result: %i", fibonacci(8));
  DBG("[Lesson 1]: Functions 10 [END]");
  return 0;
}

