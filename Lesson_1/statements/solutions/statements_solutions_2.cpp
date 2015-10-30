#include <cmath>
#include <cstdlib>
#include <ctime>
#include "logger.h"

int power(int value, int base) {
  int b = 1;
  while (base != 0) {
    if (base % 2 == 0) {
      base /= 2;
      value *= value;
    } else {
      --base;
      b *= value;
    }
  }
  return b;
}

void unitTest() {
  clock_t start = clock();
  clock_t elapsed = start;
  bool flag = true;

  while (flag && (elapsed - start) < 1 * CLOCKS_PER_SEC) {
    int value = rand() % 10 + 1;
    int base = rand() % 10;

    int expected = pow(value, base);
    int actual = power(value, base);

    if (expected != actual) {
      ERR("Error: %i ^ %i -> expected = %i, actual = %i", value, base, expected, actual);
      flag = false;
    } else {
      INF("OK");
    }
    elapsed = clock();
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements: Solutions 2");
  unitTest();
  DBG("[Lesson 1]: Statements: Solutions 2 [END]");
  return 0;
}

