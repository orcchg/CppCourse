#include <cstdlib>
#include "logger.h"

void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 3");

  int* array = new int[10];
  
  for (size_t i = 0; i < 10; ++i) {
    array[i] = std::rand() % 100 + 1;
  }
  print(array, 10);

  delete [] array;

  DBG("[Lesson 1]: Arrays 3 [END]");
  return 0;
}

