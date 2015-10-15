#include <algorithm>
#include "logger.h"

namespace sort {

size_t partition(int array[], size_t p, size_t r) {
  int pivot = array[r - 1];
  size_t i = p;

  for (size_t j = p + 1; j < r; ++j) {
    if (array[j - 1] <= pivot) {
      ++i;
      std::swap(array[i - 1], array[j - 1]);
    }
  }
  std::swap(array[i], array[r - 1]);
  return i;
}

void quicksort(int array[], size_t p, size_t r) {
  if (p < r) {
    size_t q = partition(array, p, r);
    quicksort(array, p, q);
    quicksort(array, q + 1, r);
  }
}

void quicksort(int array[], size_t size) {
  quicksort(array, 0, size);
}

}

void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Quick sort");

  int array[20] = {5, 8, 1, 12, -4, -7, 3, 5, 9, 0, 17, -4, -8, 11, 3, 7, 6, -11, -9, 2};
  print(array, 20);
  INF("After sorting");
  sort::quicksort(array, 20);
  print(array, 20);

  DBG("[Lesson 1]: Sortings: Quick sort [END]");
  return 0;
}

