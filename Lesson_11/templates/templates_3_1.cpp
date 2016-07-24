#include <cmath>
#include <cstdio>
#include "logger.h"

struct Point {
  float x, y;
};

float distance(const Point& a, const Point& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool operator < (const Point& a, const Point& b) {
  Point ZERO = {0.0, 0.0};
  return distance(a, ZERO) < distance(b, ZERO);
}

bool operator > (const Point& a, const Point& b) {
  Point ZERO = {0.0, 0.0};
  return distance(a, ZERO) > distance(b, ZERO);
}

/* Copy */
// ----------------------------------------------------------------------------
template <typename T>
void copy(T source[], T dest[], size_t size, size_t offset) {
  for (size_t i = 0; i < size; ++i) {
    dest[i] = source[i + offset];
  }
}

/* Merge */
// ----------------------------------------------
template <typename T>
void merge(T left[], size_t left_size, T right[], size_t right_size, T array[]) {
  size_t k = 0, l = 0, r = 0;
  while (l < left_size && r < right_size) {
    T left_key = left[l];
    T right_key = right[r];
    if (left_key < right_key) {
      array[k] = left_key;
      ++l;
    } else {
      array[k] = right_key;
      ++r;
    }
    ++k;
  }

  if (l == left_size) {
    while (r < right_size) {
      array[k] = right[r];
      ++k, ++r;
    }
  }

  if (r == right_size) {
    while (l < left_size) {
      array[k] = left[l];
      ++k, ++l;
    }
  }
}

/* Sorting */
// ----------------------------------------------------------------------------
template <typename T>
void mergeSort(T array[], size_t size) {
  if (size < 2) {
    return;
  }
  size_t left_size = size / 2;
  size_t right_size = size - left_size;
  T left[left_size];
  T right[right_size];

  copy<T>(array, left, left_size, 0);
  copy<T>(array, right, right_size, left_size);
  mergeSort<T>(left, left_size);
  mergeSort<T>(right, right_size);
  merge<T>(left, left_size, right, right_size, array);
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

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 11]: Templates 3.1");

  int integers[] = {5, -2, 0, 6, -8, 4, 3};
  size_t sizei = sizeof(integers) / sizeof(integers[0]);
  mergeSort<int>(integers, sizei);
  printArray<int>(integers, sizei);
  
  float floats[] = {3.14, 2.71, -0.05, 0.02, -0.4, 0.7};
  size_t sizef = sizeof(floats) / sizeof(floats[0]);
  mergeSort<float>(floats, sizef);
  printArray<float>(floats, sizef);

  Point points[] = {{3.14, 2.71}, {0.05, 2.7}, {-1.0, 0.5}, {0.02, -0.04}};
  size_t sizep = sizeof(points) / sizeof(points[0]);
  mergeSort<Point>(points, sizep);
  printArray<Point>(points, sizep);

  DBG("[Lesson 11]: Templates 3.1 END");
  return 0;
}

