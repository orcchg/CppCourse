#include <cstdio>
#include "logger.h"

int lcm(int first, int second) {
  int u = second;
  int v = first;

  while (first > 0 && second > 0) {
    if (first >= second) {
      first -= second;
      v += u;
    } else {
      second -= first;
      u += v;
    }
  }

  if (first == 0) {
    return v / 2;
  } else {
    return u / 2;
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements 3");

  int first, second;
  scanf("%i %i", &first, &second);
  INF("lcm(%i, %i) = %i", first, second, lcm(first, second));

  DBG("[Lesson 1]: Statements 3 [END]");
  return 0;
}

