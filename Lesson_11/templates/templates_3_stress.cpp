#include <algorithm>
#include <random>
#include <cmath>
#include <cstdio>
#include "logger.h"

struct Point {
  float x, y;
};

float distance(const Point& a, const Point& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool operator == (const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (const Point& a, const Point& b) {
  return a.x != b.x || a.y != b.y;
}

bool operator < (const Point& a, const Point& b) {
  Point ZERO = {0.0, 0.0};
  return distance(a, ZERO) < distance(b, ZERO);
}

bool operator > (const Point& a, const Point& b) {
  Point ZERO = {0.0, 0.0};
  return distance(a, ZERO) > distance(b, ZERO);
}

/* Sorting */
// ----------------------------------------------------------------------------
template <typename T>
void insertionSort(T array[], size_t size) {
  for (size_t i = 1; i < size; ++i) {
    T key = array[i];
    int j = i - 1;
    while (j >= 0 && array[j] > key) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

/* Print */
// ----------------------------------------------------------------------------
template <typename T>
void print(T obj);

template <>
void print<int>(int value) {
  printf("%i", value);
}

template <>
void print<float>(float value) {
  printf("%.2f", value);
}

template <>
void print<Point>(Point obj) {
  printf("(%.2f, %.2f)", obj.x, obj.y);
}

template <typename T>
void printArray(T array[], size_t size) {
  char delimiter = '\0';
  printf("[");
  for (size_t i = 0; i < size; ++i) {
    printf("%c", delimiter);
    print<T>(array[i]);
    delimiter = ' ';
  }
  printf("]\n");
}

/* Generate */
// ----------------------------------------------
template <typename T>
void generate(T array[], size_t size);

template <>
void generate<int>(int array[], size_t size) {
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(10, 99);
  for (size_t i = 0; i < size; ++i) {
    array[i] = distribution(generator);
  }
}

template <>
void generate<float>(float array[], size_t size) {
  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(-1.0, 1.0);
  for (size_t i = 0; i < size; ++i) {
    array[i] = distribution(generator);
  }
}

template <>
void generate<Point>(Point array[], size_t size) {
  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(-1.0, 1.0);
  for (size_t i = 0; i < size; ++i) {
    array[i] = {distribution(generator), distribution(generator)};
  }
}

/* Compare */
// ----------------------------------------------
template <typename T>
bool compareArrays(T lhs[], T rhs[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

/* Copy */
// ----------------------------------------------
template <typename T>
void copy(T source[], T dest[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    dest[i] = source[i];
  }
}

/* Stress test */
// ----------------------------------------------
template <typename T>
void test() {
  while (true) {
    size_t size = rand() % 1000 + 1;
    T array[size], backup[size];
    generate<T>(array, size);
    copy(array, backup, size);
    insertionSort<T>(array, size);
    std::sort(backup, backup + size);
    if (!compareArrays(array, backup, size)) {
      ERR("Fail");
      break;
    } else {
      INF("OK");
    }
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 11]: Templates 3 stress-test");

  //test<int>();
  //test<float>();
  test<Point>();

  DBG("[Lesson 11]: Templates 3 stress-test END");
  return 0;
}

