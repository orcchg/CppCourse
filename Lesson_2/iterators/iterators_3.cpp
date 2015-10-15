#include <cstdio>
#include "logger.h"

/* Array */
// ----------------------------------------------------------------------------
struct Array {
  size_t size;
  int* data;

  void init(int array[], size_t size);
  void print();
};

void Array::init(int* array, size_t sz) {  // Quiz: implement deep copy
  size = sz;
  data = array;
}

void Array::print() {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", data[i]);
  }
  printf("\n");
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: Iterators 3");

  int values[] = {5, 8, -9, 17, 4, 2, -3, 0, 11, 6};
  size_t size = sizeof(values) / sizeof(values[0]);

  Array array;
  array.init(values, size);
  array.print();

  DBG("[Lesson 2]: Iterators 3 [END]");
}

