#include <vector>
#include <cstdlib>
#include "logger.h"

int compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

bool oldFunction(int array[], size_t size, int x) {
  qsort(array, size, sizeof(int), compare);
  return bsearch(&x, array, size, sizeof(int), compare) != nullptr;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 17");

  int x = 0;
  printf("Enter a number: ");
  scanf("%i", &x);

  std::vector<int> array = {5, 10, 15, 11, 9, 4, -6, 8, 17, 22, 3, -2, 1, 0};
  bool found = oldFunction(&array[0], array.size(), x);

  if (found) {
    INF("Found %i in array", x);
  } else {
    WRN("Not found %i in array", x);
  }

  DBG("[Lesson 1]: Arrays 17 [END]");
  return 0;
}

