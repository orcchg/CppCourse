#include <cstdio>
#include "logger.h"

#define SIZE 24

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 4");

  char string[SIZE];

  int days = 31;
  int month = 10;
  int year = 2015;

  snprintf(string, SIZE, "October is a %ith month in year %i with %i days total", month, days, year);
  printf("String: %s\n", string);

  DBG("[Lesson 2]: IO 4 [END]");
  return 0;
}

