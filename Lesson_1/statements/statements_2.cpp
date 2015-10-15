#include <cstdio>
#include "logger.h"

int gcd(int first, int second) {
  while (first > 0 && second > 0) {
    if (first >= second) {
      first -= second;
    } else {
      second -= first;
    }
  }

  if (first == 0) {
    return second;
  } else {
    return first;
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements 2");

  int first, second;
  scanf("%i %i", &first, &second);
  INF("gcd(%i, %i) = %i", first, second, gcd(first, second));

  DBG("[Lesson 1]: Statements 2 [END]");
  return 0;
}

