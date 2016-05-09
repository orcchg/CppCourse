#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 13");

  std::vector<int> blocks = {100, 200, 700, 400, 200, 50, 350};
  std::make_heap(blocks.begin(), blocks.end());

  std::copy(blocks.begin(), blocks.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  INF("Max heap: %i", blocks.front());

  std::pop_heap(blocks.begin(), blocks.end());
  blocks.pop_back();  // Removes rearranged element from back
  DBG("Pop heap: %i", blocks.front());
  std::copy(blocks.begin(), blocks.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  int item = 800;
  blocks.push_back(item);
  std::push_heap(blocks.begin(), blocks.end());
  WRN("Push %i heap: %i", item, blocks.front());
  std::copy(blocks.begin(), blocks.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Algorithms 13 END");
  return 0;
}

