#include <vector>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 11");

  std::vector<int> array = {5, 10, 15, 11, 9, 4, -6, 8, 1, 22, 3, -2, 1, 0};
  for (int i = 0; i < array.size(); ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");

  DBG("[Lesson 1]: Arrays 11 [END]");
  return 0;
}

