#include <string>
#include <cstdio>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: STD string 0");

  std::string str;
  scanf("%s", str.c_str());
  printf("%s\n", str.c_str());

  DBG("[Lesson 2]: STD string 0 [END]");
  return 0;
}

