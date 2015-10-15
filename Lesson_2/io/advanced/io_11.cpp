#include <iostream>
#include <vector>
#include <cstdio>
#include "logger.h"

int main(int argc, char** argv) {  // Quiz: compare performance
  DBG("[Lesson 2]: IO 11");

  std::vector<int> array = {5, -7, -3, 8, 4, 0, 9, -11, 1, 2, 10};

  // standard io
  for (size_t i = 0; i < array.size(); ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");

  // streams
  for (size_t i = 0; i < array.size(); ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;

  // standard io + for_each
  for (int item : array) {
    printf("%i ", item);
  }
  printf("\n");

  // streams + for_each
  for (int item : array) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  DBG("[Lesson 2]: IO 11 [END]");
  return 0;
}

