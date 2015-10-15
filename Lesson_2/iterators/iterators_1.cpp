#include <string>
#include <vector>
#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: Iterators 1");

  std::vector<std::string> array = {"This", "is", "lesson", "two", "part", "of", "iterators", "concept"};
  for (auto it = array.begin(); it != array.end(); ++it) {
    printf("%s ", it->c_str());
  }
  printf("\n");

  DBG("[Lesson 2]: Iterators 1 [END]");
}

