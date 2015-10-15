#include <string>
#include <vector>
#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: Iterators 2");

  std::vector<std::string> array = {"This", "is", "lesson", "two", "part", "of", "iterators", "concept"};
  for (auto it = array.begin(); it != array.end(); ++it) {
    for (auto sit = it->begin(); sit != it->end(); ++sit) {
      printf("%c ", *sit);
    }
    printf("\n");
  }

  DBG("[Lesson 2]: Iterators 2 [END]");
}

