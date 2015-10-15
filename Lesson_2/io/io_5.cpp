#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 5");

  int c;
  puts("Enter text. Include a dot ('.') in a sentence to exit:");
  do {
    c=getchar();
    putchar (c);
  } while (c != '.');

  DBG("[Lesson 2]: IO 5 [END]");
  return 0;
}

