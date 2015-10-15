#include <cstdlib>
#include "logger.h"

void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 2");

  int* array = (int*) malloc(sizeof(int) * 10);
  
  for (size_t i = 0; i < 10; ++i) {
    array[i] = std::rand() % 100 + 1;
  }
  print(array, 10);

  free(array);

  DBG("[Lesson 1]: Arrays 2 [END]");
  return 0;
}

