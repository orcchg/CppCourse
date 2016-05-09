#include <algorithm>
#include <string>
#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 11");

  std::string raw = "The string with *formatted block* surrounded with asteriskes";
  std::replace(raw.begin(), raw.end(), '*', ' ');
  printf("%s\n", raw.c_str());

  DBG("[Lesson 4]: Algorithms 11 END");
  return 0;
}

