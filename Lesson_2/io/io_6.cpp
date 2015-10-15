#include <cstdio>
#include "logger.h"

#define SIZE 24

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 6");

  char buffer[SIZE];

  char ch;
  int index = 0;
  do {
    ch = getchar();
    buffer[index++] = ch;
  } while (ch != '\n' && index < SIZE);

  INF("Buffer: %s", buffer);

  DBG("[Lesson 2]: IO 6 [END]");
  return 0;
}

