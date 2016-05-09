#include <algorithm>
#include <string>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 14");

  std::string lorem = "Lorem";  // TODO[Quiz]: put to lower case
  std::string ipsum = "ipsum";

  bool result = std::lexicographical_compare(lorem.begin(), lorem.end(), ipsum.begin(), ipsum.end());

  if (result) {
    INF("%s < %s", lorem.c_str(), ipsum.c_str());
  } else {
    WRN("%s >= %s", lorem.c_str(), ipsum.c_str());
  }

  DBG("[Lesson 4]: Algorithms 14 END");
  return 0;
}

