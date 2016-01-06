#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include "logger.h"

#define SIZE 10

template <typename T>
class Array {
public:
  Array(size_t size);
  ~Array();

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  inline T* begin() { return m_data; }
  inline T* end() { return m_data + m_size; }

  inline size_t getSize() const { return m_size; }

private:
  size_t m_size;
  T* m_data;
};

template <typename T>
Array<T>::Array(size_t size)
  : m_size(size)
  , m_data(new T[size]) {
}

template <typename T>
Array<T>::~Array() {
  delete [] m_data;
}

template <typename T>
T& Array<T>::operator[](size_t index) {
  return m_data[index];
}

template <typename T>
const T& Array<T>::operator[](size_t index) const {
  return m_data[index];
}

/* Advance iterator */
// ----------------------------------------------------------------------------
template <typename Iterator, typename Tag>
void advanceIterator_inner(Iterator& iterator, size_t shift, Tag tag) {
  while (shift > 0) {
    ++iterator;
    --shift;
  }
}

/* Template specialization */
// ----------------------------------------------------------------------------
template <typename Iterator>
void advanceIterator_inner(Iterator& iterator, size_t shift, std::random_access_iterator_tag tag) {
  iterator += shift;
}

/* Iterator traits */
// ----------------------------------------------------------------------------
template <typename Iterator>
void advanceIterator(Iterator& iterator, size_t shift) {
  // deduce iterator tag from iterator's type
  typename std::iterator_traits<Iterator>::iterator_category tag;

  advanceIterator_inner(iterator, shift, tag);
}

/* Main */
// ----------------------------------------------------------------------------
void fill(Array<int>* array) {
  for (size_t i = 0; i < array->getSize(); ++i) {
    array->operator[](i) = rand() % 100;  // Quiz: re-write much compactly
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 6]: Iterators 4");

  Array<int> numbers(SIZE);
  fill(&numbers);
  std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));  std::cout << std::endl;

  auto iterator = numbers.begin();

  advanceIterator(iterator, 5);
  INF("Shifted iterator: %i", *iterator);

  DBG("[Lesson 6]: Iterators 4 [END]");
  return 0;
}

