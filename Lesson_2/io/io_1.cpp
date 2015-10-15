#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 1");

  char* string = new char[256];

  printf("Input string: ");
  scanf("%s", string);
  printf("String is: %s\n", string);

  delete [] string;
  string = nullptr;

  DBG("[Lesson 2]: IO 1 [END]");
  return 0;
}

