#include <cstdio>
#include "logger.h"

/**
 * Inheritance: polymorphism in pure C
 */
struct Square {
  int width;
  int height;
};

struct Circle {
  float radius;
};

struct Triangle {
  int base;
  int height;
};

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: C Style 2");

  printf("size of square is %i\n", sizeof(Square));
  printf("size of Circle is %i\n", sizeof(Circle));
  printf("size of Triangle is %i\n", sizeof(Triangle));

  DBG("[Lesson 5]: C Style 2 [END]");
  return 0;
}

