#include <cstdio>
#include "logger.h"

struct Point {
  float x, y;
};

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

int main(int argc, char** argv) {
  DBG("[Lesson 11]: Templates 0");

  int integers[] = {5, -2, 0, 6, -8, 4, 3};
  printArray<int>(integers, sizeof(integers) / sizeof(integers[0]));

  float floats[] = {3.14, 2.71, -0.05, 0.02, -0.4, 0.7};
  printArray<float>(floats, sizeof(floats) / sizeof(floats[0]));

  Point points[] = {{3.14, 2.71}, {0.05, 2.7}, {-1.0, 0.5}, {0.02, -0.04}};
  printArray<Point>(points, sizeof(points) / sizeof(points[0]));

  DBG("[Lesson 11]: Templates 0 END");
  return 0;
}

