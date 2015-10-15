#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: C String 2");

  const char* source = "Hello, World!\n";
  char destination[8];

  strncpy(destination, source, 8);
  printf("%s\n", destination);

  DBG("[Lesson 2]: C String 2 [END]");
  return 0;
}

