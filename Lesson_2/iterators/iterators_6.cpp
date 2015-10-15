#include <iostream>
#include <string>
#include <cstdio>
#include "logger.h"

/* Array */
// ----------------------------------------------------------------------------
template <typename T>
struct Array {
  typedef T* iterator;

  size_t size;
  T* data;

  void init(T* array, size_t size);
  void print();

  iterator begin();
  iterator end();
};

template <typename T>
void Array<T>::init(T* array, size_t sz) {
  size = sz;
  data = array;
}

template <typename T>  // Quiz: why not printf() ?
void Array<T>::print() {
  for (iterator it = begin(); it != end(); ++it) {
    std::cout << *it << " ";
  }
  printf("\n");
}

/* Iterator member-functions */
// ----------------------------------------------
template <typename T>
typename Array<T>::iterator Array<T>::begin() {
  return data;
}

template <typename T>
typename Array<T>::iterator Array<T>::end() {
  return data + size;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: Iterators 6");

  int int_values[] = {5, 8, -9, 17, 4, 2, -3, 0, 11, 6};
  size_t int_size = sizeof(int_values) / sizeof(int_values[0]);

  Array<int> int_array;
  int_array.init(int_values, int_size);
  int_array.print();

  std::string str_values[] = {"Here", "is", "an", "example", "of", "template", "structure", "so", "beware!"};
  size_t str_size = sizeof(str_values) / sizeof(std::string);

  Array<std::string> str_array;
  str_array.init(str_values, str_size);
  str_array.print();

  DBG("[Lesson 2]: Iterators 6 [END]");
}

