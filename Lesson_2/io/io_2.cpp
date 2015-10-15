#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 2");

  const char* string = "Hello 365 days!";

  int days = 0;
  sscanf(string, "%*s %i %*s", &days);
  printf("Days: %i\n", days);

  DBG("[Lesson 2]: IO 2 [END]");
  return 0;
}

