#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: C String 0");

  const char* source = "Hello, World!\n";
  printf("Length: %zu\n", strlen(source));

  DBG("[Lesson 2]: C String 0 [END]");
  return 0;
}

