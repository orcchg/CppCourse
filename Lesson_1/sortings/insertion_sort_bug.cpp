#include "logger.h"

namespace sort {

void insertion(int array[], size_t size) {
  for (size_t j = 1; j < size; ++j) {
    int key = array[j];
    size_t i = j - 1;
    while (i > 0 && array[i] > key) {
      array[i + 1] = array[i];
      --i;
    }
    array[i + 1] = key;
  }
}

}

void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Insertion sort bug");

  int array[10] = {5, 8, 1, 12, -4, -7, 3, 5, 9, 0};
  print(array, 10);
  INF("After sorting");
  sort::insertion(array, 10);
  print(array, 10);

  DBG("[Lesson 1]: Sortings: Insertion sort bug [END]");
  return 0;
}

