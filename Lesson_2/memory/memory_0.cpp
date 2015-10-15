#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: Memory 1");

  char source[] = "almost every programmer should know memset!";
  memset(source, '-', 6);  // conversion from 'int' to 'uchar'
  puts(source);

  DBG("[Lesson 2]: Memory 1 [END]");
  return 0;
}

