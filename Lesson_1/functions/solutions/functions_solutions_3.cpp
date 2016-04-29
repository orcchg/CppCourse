#include "logger.h"

int doSomething(int z, int& a, int* c) {
  a = z + *c;
  *c = z * 2 - a;
  return a + *c;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions: Solutions 3");
  int z = 10;
  int a = 5;
  int c = 2;
  int r = doSomething(z, a, &c);
  INF("Z: %i, A: %i, C: %i, R: %i", z, a, c, r);
  DBG("[Lesson 1]: Functions: Solutions 3 [END]");
  return 0;
}

