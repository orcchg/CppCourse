#include <algorithm>
#include "logger.h"

namespace home {

template <typename T>
void swap(T& lhs, T& rhs) {
  T temporary = rhs;
  rhs = lhs;
  lhs = temporary;
}

}

void unitTest() {
  int a = 5, b = 7;
  std::swap(a, b);
  home::swap(a, b);
  if (a != 5 && b != 7) {
    ERR("Error!");
  } else {
    INF("OK");
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions: Solutions 2");
  unitTest();
  DBG("[Lesson 1]: Functions: Solutions 2 [END]");
  return 0;
}

