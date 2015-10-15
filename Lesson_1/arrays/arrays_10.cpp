#include <vector>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 10");

  std::vector<int> array = {5, 10, 15, 11, 9, 4, -6, 8, 17, 22, 3, -2, 1, 0};
  INF("Size: %zu", array.size());

  DBG("[Lesson 1]: Arrays 10 [END]");
  return 0;
}

