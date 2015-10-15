#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: Memory 2");

  char source[] = "almost every programmer should know memset!";
  char destination[12];

  memcpy(destination, source, 6);
  puts(destination);

  DBG("[Lesson 2]: Memory 2 [END]");
  return 0;
}

