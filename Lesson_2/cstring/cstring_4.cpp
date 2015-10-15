#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: C String 4");

  printf("\e[5;00;33mВедите первую строку: \e[m");
  char first[256];
  gets(first);

  printf("\e[5;00;34mВедите вторую строку: \e[m");
  char second[256];
  gets(second);

  int result = strcmp(first, second);
  if (result > 0) {
    WRN("%s is lexicographical greater than %s", first, second);
  } else if (result < 0) {
    WRN("%s is lexicographical less than %s", first, second);
  } else {
    INF("%s is equal to %s", first, second);
  }

  DBG("[Lesson 2]: C String 4 [END]");
  return 0;
}

