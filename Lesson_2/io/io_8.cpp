#include <cstdio>
#include "logger.h"

#define SIZE 24

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 8");

  char buffer[SIZE];
  printf("String: %s\n", gets(buffer));

  DBG("[Lesson 2]: IO 8 [END]");
  return 0;
}

