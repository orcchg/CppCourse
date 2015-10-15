#include <cstdlib>
#include "logger.h"

void print(int* array, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", i[array]);
  }
  printf("\n");
}

void copy(int source[], int destination[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    *destination++ = *source++;
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 7");

  int* A = new int[10];
  int* B = new int[10];
  
  for (size_t i = 0; i < 10; ++i) {
    A[i] = std::rand() % 100 + 1;
  }

  copy(A, B, 10);
  print(A, 10);
  print(B, 10);

  delete [] A;
  delete [] B;

  DBG("[Lesson 1]: Arrays 7 [END]");
  return 0;
}

