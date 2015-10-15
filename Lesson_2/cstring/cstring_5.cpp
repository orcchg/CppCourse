#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: C String 5");

  printf("\e[5;00;34mВедите строку: \e[m");
  char string[256];
  gets(string);

  printf("\e[5;00;33mВедите искомый символ: \e[m");
  char ch = getchar();

  char* ptr = strchr(string, static_cast<int>(ch));
  if (ptr != nullptr) {
    INF("Найден символ %c на позиции %li", ch, ptr - string + 1);
  } else {
    WRN("Символ не найден!");
  }

  DBG("[Lesson 2]: C String 5 [END]");
  return 0;
}

