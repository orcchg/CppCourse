#include <vector>
#include <cstdlib>
#include <ctime>
#include "logger.h"

int generate() {
  srand(clock());
  return rand() % 32768;
}

bool isPrime(int value) {
  if (value <= 0) {
    return false;
  } else if (value == 1) {
    return true;
  }

  int key = value;
  int divider = 2;

  while (divider != value) {
    if (key % divider == 0) {
      return false;
    } else {
      ++divider;
    }
  }

  return divider == value;
}

void fill(std::vector<int>* array) {
  int size = generate();
  for (int i = 0; i < size; ++i) {
    int value = generate();
    array->push_back(value);
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 13");

  std::vector<int> random_values;
  random_values.reserve(10);  // capacity
  DBG("Fill size [%zu] (capacity [%zu])", random_values.size(), random_values.capacity());

  clock_t start = clock();
  clock_t end = clock();
  while (end - start <= CLOCKS_PER_SEC * 5) {
    clock_t up = clock();
    fill(&random_values);
    clock_t down = clock() - up;
    double elapsed = static_cast<double>(down) / CLOCKS_PER_SEC;
    INF("Fill size [%zu] (capacity [%zu]) by time: %lf", random_values.size(), random_values.capacity(), elapsed);
    random_values.clear();
    end = clock();
  }

  DBG("[Lesson 1]: Arrays 13 [END]");
  return 0;
}

