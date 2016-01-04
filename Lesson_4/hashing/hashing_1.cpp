#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Hashing 1");

  // Quiz: compare the order of elements with tree_set
  std::unordered_set<std::string> hash_set = {"Lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing", "elit"};

  std::copy(hash_set.begin(), hash_set.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Hashing 1 [END]");
  return 0;
}

