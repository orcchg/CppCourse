#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "logger.h"

void print(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end) {
  std::copy(begin, end, std::ostream_iterator<int>(std::cout, " "));
  printf("\n");
}

struct SortedVector {
  std::vector<int> array;

  void push_back(int value);
};

void SortedVector::push_back(int value) {
  if (array.empty() || array.back() <= value) {
    array.push_back(value);
    return;
  }

  size_t i = array.size() - 1;
  while (i >= 0) {
    if (array[i] < value) {
      break;
    }
    --i;
  }

  std::vector<int> new_array;
  new_array.reserve(array.size() * 2);
  if (i < 0) {
    new_array.push_back(value);
    new_array.insert(new_array.end(), array.begin(), array.end());
  } else {
    new_array.assign(array.begin(), array.begin() + i + 1);
    new_array.push_back(value);
    new_array.insert(new_array.end(), array.begin() + i + 1, array.end());
  }
  std::swap(array, new_array);
  print(array.begin(), array.end());
  new_array.clear();
}

void unitTest() {
  clock_t start = clock();
  clock_t elapsed = start;

  while ((elapsed - start) < 5 * CLOCKS_PER_SEC) {
    int size = rand() % 10 + 1;
    std::vector<int> sorted_vector;
    SortedVector testing_vector;

    DBG("%i", size);
    for (int i = 0; i < size; ++i) {
      int value = rand() % 100;
      sorted_vector.push_back(value);
      testing_vector.push_back(value);
    }
    print(sorted_vector.begin(), sorted_vector.end());
    std::sort(sorted_vector.begin(), sorted_vector.end());

    if (sorted_vector != testing_vector.array) {
      ERR("Error: expected VS actual");
      print(sorted_vector.begin(), sorted_vector.end());
      print(testing_vector.array.begin(), testing_vector.array.end());
      break;
    } else {
      INF("OK: %i", size);
    }

    elapsed = clock();
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays: Solutions 6");
  unitTest();
  DBG("[Lesson 1]: Arrays: Solutions 6 [END]");
  return 0;
}

