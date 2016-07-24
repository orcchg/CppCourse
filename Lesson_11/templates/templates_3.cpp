#include <cmath>
#include <cstdio>
#include "logger.h"

struct Point {
  float x, y;
};

float distance(const Point& a, const Point& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
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

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 11]: Templates 3");

  int integers[] = {5, -2, 0, 6, -8, 4, 3};
  size_t sizei = sizeof(integers) / sizeof(integers[0]);
  insertionSort<int>(integers, sizei);
  printArray<int>(integers, sizei);
  
  float floats[] = {3.14, 2.71, -0.05, 0.02, -0.4, 0.7};
  size_t sizef = sizeof(floats) / sizeof(floats[0]);
  insertionSort<float>(floats, sizef);
  printArray<float>(floats, sizef);

  Point points[] = {{3.14, 2.71}, {0.05, 2.7}, {-1.0, 0.5}, {0.02, -0.04}};
  size_t sizep = sizeof(points) / sizeof(points[0]);
  insertionSort<Point>(points, sizep);
  printArray<Point>(points, sizep);

  DBG("[Lesson 11]: Templates 3 END");
  return 0;
}

