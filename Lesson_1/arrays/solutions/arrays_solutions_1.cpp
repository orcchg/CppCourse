#include <algorithm>
#include <cstdio>
#include "logger.h"

void revert(int array[], size_t size) {
  for (size_t i = 0; i < size / 2; ++i) {
    std::swap(array[i], array[size - i - 1]);
  }
}

void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays: Solutions 1");
  int array[8] = {5, 4, -7, 8, 0, 11, -2, 3};
  print(array, 8);
  revert(array, 8);
  print(array, 8);
  DBG("[Lesson 1]: Arrays: Solutions 1 [END]");
  return 0;
}

