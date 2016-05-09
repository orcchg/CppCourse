#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 9");

  std::vector<char> password = {'a', 'b', 'c'};
  std::sort(password.begin(), password.end());

  do {
    std::copy(password.begin(), password.end(), std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;
  } while (std::next_permutation(password.begin(), password.end()));

  DBG("[Lesson 4]: Algorithms 9 END");
  return 0;
}

