#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: C String 3");

  const char* source = "World!";
  char destination[48];

  strcpy(destination, "Hello, ");
  strcat(destination, source);

  printf("%s\n", destination);

  DBG("[Lesson 2]: C String 3 [END]");
  return 0;
}

