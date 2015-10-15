#include <cstdio>
#include "logger.h"

#define SIZE 24

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 7");

  char buffer[SIZE];

  char ch;
  int index = 0;
  while ((ch = getchar()) != '\n' && index < SIZE) {
    buffer[index++] = ch;
  }

  INF("Buffer: %s", buffer);

  DBG("[Lesson 2]: IO 7 [END]");
  return 0;
}

