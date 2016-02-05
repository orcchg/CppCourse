#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "logger.h"

void performanceTest() {
  clock_t start = clock();
  clock_t elapsed = start;
  size_t min_size = +99999, max_size = 0;
  double min_ratio = +99999, max_ratio = 0;

  while ((elapsed - start) < 1 * CLOCKS_PER_SEC) {
    size_t size = rand() % 65536 + 10000;
    std::string str = "";
    std::vector<char> array;

    clock_t start_time = clock();
    for (size_t i = 0; i < size; ++i) {
      char ch = rand() % 58 + 'A';
      str.push_back(ch);
    }
    clock_t str_elapsed = clock();
    for (size_t i = 0; i < size; ++i) {
      char ch = rand() % 58 + 'A';
      array.push_back(ch);
    }
    clock_t array_elapsed = clock();

    double str_time = static_cast<double>(str_elapsed - start_time) / CLOCKS_PER_SEC;
    double array_time = static_cast<double>(array_elapsed - str_elapsed) / CLOCKS_PER_SEC;
    double ratio = str_time / array_time;
    INF("Size = %zu, String [%.8lf], Vector [%.8lf], ratio = %.8lf", size, str_time, array_time, ratio);

    if (min_ratio > ratio) { min_ratio = ratio; }
    if (max_ratio < ratio) { max_ratio = ratio; }
    if (min_size > size) { min_size = size; }
    if (max_size < size) { max_size = size; }

    elapsed = clock();
  }
  WRN("Size: min [%zu], max [%zu]; Ratio: min [%.8lf], max [%.8lf]", min_size, max_size, min_ratio, max_ratio);
}

int main(int argc, char** argv) {
  DBG("[Lesson 2]: STD string: Solutions 3");
  performanceTest();
  DBG("[Lesson 2]: STD string: Solutions 3 [END]");
  return 0;
}

