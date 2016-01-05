#include <cstdio>
#include "logger.h"

// @see http://www.codeproject.com/Articles/739687/Achieving-polymorphism-in-C

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
  DBG("[Lesson 5]: C Style 3");

  printf("size of square is %lu\n", sizeof(Square));
  printf("size of Circle is %lu\n", sizeof(Circle));
  printf("size of Triangle is %lu\n", sizeof(Triangle));

  // check data alignment in Square instance
  Square square;
  square.width = 1;
  square.height = 2;
  printf("the first 4 bytes of square are %i", (*(int*)(&square)));
  printf("the second 4 bytes of square are %d\n", (*(int*)&square + 1));

  DBG("[Lesson 5]: C Style 3 [END]");
  return 0;
}

