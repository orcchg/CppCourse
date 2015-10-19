#include "logger.h"

int fibonacci(int N) {
  int prev = 0, next = 1;

  int answer = 0;
  while (N-- > 0) {
    answer = prev + next;
    prev = next;
    next = answer;
  }
  return answer;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions: Solutions 5");
  INF("Fibonacci: %i", fibonacci(8));
  DBG("[Lesson 1]: Functions: Solutions 5 [END]");
  return 0;
}

