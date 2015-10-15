#include <cstdio>
#include "logger.h"

/* Array */
// ----------------------------------------------------------------------------
struct Array {
  size_t size;
  int* data;

  void init(int array[], size_t size);
  void print();

  int* begin();
  int* end();
};

void Array::init(int* array, size_t sz) {
  size = sz;
  data = array;
}

void Array::print() {
  for (int* it = begin(); it != end(); ++it) {
    printf("%i ", *it);
  }
  printf("\n");
}

/* Iterator member-functions */
// ----------------------------------------------
int* Array::begin() {
  return data;
}

int* Array::end() {
  return data + size;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: Iterators 4");

  int values[] = {5, 8, -9, 17, 4, 2, -3, 0, 11, 6};
  size_t size = sizeof(values) / sizeof(values[0]);

  Array array;
  array.init(values, size);
  array.print();

  DBG("[Lesson 2]: Iterators 4 [END]");
}

