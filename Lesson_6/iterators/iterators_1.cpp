#include <iterator>
#include <vector>
#include "logger.h"

template <typename Iterator, typename Tag>
void advanceIterator(Iterator& iterator, size_t shift, Tag tag) {
  while (shift > 0) {
    ++iterator;
    --shift;
  }
}

/* Template specialization */
// ----------------------------------------------------------------------------
template <typename Iterator>
void advanceIterator(Iterator& iterator, size_t shift, std::random_access_iterator_tag tag) {
  iterator += shift;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 6]: Iterators 1");

  std::vector<int> numbers = {0, 6, 2, -1, 4, 7, 5};
  auto iterator = numbers.begin();

  std::random_access_iterator_tag rdm_tag;  // excess declaration

  advanceIterator(iterator, 5, rdm_tag);
  INF("Shifted iterator: %i", *iterator);

  DBG("[Lesson 6]: Iterators 1 [END]");
  return 0;
}

