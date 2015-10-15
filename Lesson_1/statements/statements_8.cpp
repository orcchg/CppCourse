#include <cstdio>
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

void looper() {
  int value = 0;
  while (true) {
    value = generate();
    if (isPrime(value)) {
      break;
    }
  }
  INF("First prime: %i", value);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements 8");

  looper();

  DBG("[Lesson 1]: Statements 8 [END]");
  return 0;
}

