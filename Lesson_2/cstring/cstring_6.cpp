#include <cstring>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: C String 6");

  printf("\e[5;00;34mВедите строку: \e[m");
  char string[256];
  gets(string);

  printf("\e[5;00;33mВедите искомую подстроку: \e[m");
  char substring[128];
  gets(substring);

  char* ptr = strstr(string, substring);
  if (ptr != nullptr) {
    INF("Найдена подстрока на позиции %li", ptr - string + 1);
  } else {
    WRN("Подстрока не найдена!");
  }

  DBG("[Lesson 2]: C String 6 [END]");
  return 0;
}

