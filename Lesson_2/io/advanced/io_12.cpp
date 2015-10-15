#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 12");

  std::vector<int> array = {5, -7, -3, 8, 4, 0, 9, -11, 1, 2, 10};
  std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::string str = "Hello, World!";
  std::copy(str.begin(), str.end(), std::ostream_iterator<char>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 2]: IO 12 [END]");
  return 0;
}

