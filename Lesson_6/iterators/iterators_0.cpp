#include <vector>
#include "logger.h"

template <typename Iterator>
Iterator& advance(Iterator& iterator, size_t shift) {
  if (/* Random Access iterator category */) {
    iterator += shift;
  } else {
    while (shift > 0) {
      ++iterator;
      --shift;
    }
  }
  return iterator;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 6]: Iterators 0");

  std::vector<int> numbers = {0, 6, 2, -1, 4, 7, 5};
  auto iterator = numbers.begin();

  advance(iterator, 5);

  DBG("[Lesson 6]: Iterators 0 [END]");
  return 0;
}

