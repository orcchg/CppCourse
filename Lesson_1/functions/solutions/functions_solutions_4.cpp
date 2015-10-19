#include "logger.h"

int factorial(int N) {
  int answer = 1;
  while (N > 0) {
    answer *= N--;
  }
  return answer;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions: Solutions 4");
  INF("Factorial: %i", factorial(8));
  DBG("[Lesson 1]: Functions: Solutions 4 [END]");
  return 0;
}

