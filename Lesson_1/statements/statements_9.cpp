#include <cstdio>
#include <ctime>
#include "logger.h"

#define SIZE 32768

int generate() {
  srand(clock());
  return rand() % SIZE;
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
  while (true) {
    int value = generate();
    int size = generate() + 1;
    for (int i = 0; i < size; ++i, value = generate()) {
      if (value >= size) {
        // skip large values
        continue;
      }
      printf("Value: %i in [%i, %i]\n", value, 0, size);
    }

    if (isPrime(value)) {
      INF("First prime: %i", value);
      return;
    }
  }
  WRN("Unreachable code!");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements 9");

  looper();

  DBG("[Lesson 1]: Statements 9 [END]");
  return 0;
}

