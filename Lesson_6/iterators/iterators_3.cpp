#include <iterator>
#include <vector>
#include "logger.h"

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
int main(int argc, char** argv) {
  DBG("[Lesson 6]: Iterators 3");

  std::vector<int> numbers = {0, 6, 2, -1, 4, 7, 5};
  auto iterator = numbers.begin();

  advanceIterator(iterator, 5);
  INF("Shifted iterator: %i", *iterator);

  DBG("[Lesson 6]: Iterators 3 [END]");
  return 0;
}

