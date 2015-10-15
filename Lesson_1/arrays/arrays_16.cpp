#include <algorithm>
#include <vector>
#include "logger.h"

bool newFunction(std::vector<int>* array, int x) {
  std::sort(array->begin(), array->end());
  return std::binary_search(array->begin(), array->end(), x);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 16");

  int x = 0;
  printf("Enter a number: ");
  scanf("%i", &x);

  std::vector<int> array = {5, 10, 15, 11, 9, 4, -6, 8, 17, 22, 3, -2, 1, 0};
  bool found = newFunction(&array, x);

  if (found) {
    INF("Found %i in array", x);
  } else {
    WRN("Not found %i in array", x);
  }

  DBG("[Lesson 1]: Arrays 16 [END]");
  return 0;
}

