#include <string>
#include <vector>
#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {  // Quiz: write all methods you know to output an array into stdout
  DBG("[Lesson 2]: Iterators 0");

  std::vector<std::string> array = {"This", "is", "lesson", "two", "part", "of", "iterators", "concept"};
  for (typename std::vector<std::string>::iterator it = array.begin(); it != array.end(); ++it) {
    printf("%s ", it->c_str());
  }
  printf("\n");

  DBG("[Lesson 2]: Iterators 0 [END]");
}

