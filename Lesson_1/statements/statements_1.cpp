#include <cstdlib>
#include <ctime>
#include "logger.h"

int generate() {
  srand(clock());
  return rand() % 32768;
}

bool isPrime(int value) {
  if (value <= 0) {
    return false;
  } else if (value == 1) {
    return true;
  }

  int key = value;
  int divider = 2;

  while (divider != value) {
    if (key % divider == 0) {
      return false;
    } else {
      ++divider;
    }
  }

  return divider == value;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements 1");

  int value = 0;
  while (!isPrime(value)) {
    value = generate();
  }
  INF("First prime: %i", value);

  DBG("[Lesson 1]: Statements 1 [END]");
  return 0;
}

