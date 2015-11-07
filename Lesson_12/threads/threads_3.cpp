#include <chrono>
#include <iostream>
#include <iomanip>
#include <numeric>  // std::accumulate
#include <random>
#include <sstream>
#include <thread>
#include <vector>
#include "logger.h"

const char* getThisThreadId() {
  std::ostringstream oss;
  oss << std::this_thread::get_id();
  return oss.str().c_str();
}

void generate(std::vector<int>* array) {
  std::minstd_rand0 rng;
  size_t size = rng() % 10000 + 1;
  array->reserve(size);
  for (size_t i = 0; i < size; ++i) {
    int value = rng() % 100;
    array->push_back(value);
  }
}

int sum(const std::vector<int>& array, size_t start, size_t end, int* output) {
  *output = std::accumulate(array.begin() + start, array.begin() + end, 0);
  DBG("Thread [%s] has finished, result: %i", getThisThreadId(), *output);
  return *output;
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Threads 3");

  std::vector<int> array;
  generate(&array);

  int left_sum = 0, right_sum = 0;

  INF("Initializing 1st thread: [%i, %zu)", 0, array.size() / 2);
  std::thread left_summator(sum, array, 0, array.size() / 2, &left_sum);
  INF("Initializing 2nd thread: [%zu, %zu)", array.size() / 2, array.size());
  std::thread right_summator(sum, array, array.size() / 2, array.size(), &right_sum);

  INF("Main thread is waiting for the whole sum...");
  left_summator.join();
  right_summator.join();

  int result = left_sum + right_sum;
  WRN("Main thread has got the sum: %i", result);

  // check
  int check = 0;
  std::cout << "Checking result: " << std::boolalpha << (sum(array, 0, array.size(), &check) == result) << std::endl;

  DBG("[Lesson 12]: Threads 3 [END]");
  return 0;
}

