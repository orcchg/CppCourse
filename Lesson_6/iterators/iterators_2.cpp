#include <iterator>
#include <vector>
#include "logger.h"

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 6]: Iterators 2");

  std::vector<int> numbers = {0, 6, 2, -1, 4, 7, 5};
  auto iterator = numbers.begin();

  std::advance(iterator, 5);  // standard function
  INF("Shifted iterator: %i", *iterator);

  DBG("[Lesson 6]: Iterators 2 [END]");
  return 0;
}

