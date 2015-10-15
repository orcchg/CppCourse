#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: C String 1");

  const char* source = "Hello, World!\n";
  char destination[256];

  strcpy(destination, source);
  printf("%s\n", destination);

  DBG("[Lesson 2]: C String 1 [END]");
  return 0;
}

