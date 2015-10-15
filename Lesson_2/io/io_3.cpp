#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 3");

  char string[256];

  int days = 31;
  int month = 10;
  int year = 2015;

  sprintf(string, "October is a %ith month in year %i with %i days total", month, days, year);
  printf("String: %s\n", string);

  DBG("[Lesson 2]: IO 3 [END]");
  return 0;
}

