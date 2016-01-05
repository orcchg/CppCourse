#include <cstdio>
#include "logger.h"

// @see http://www.codeproject.com/Articles/739687/Achieving-polymorphism-in-C

/**
 * Inheritance: polymorphism in pure C
 */
struct Square {
  int width;
  int height;

  // pointers to methods
  void (*print)();
  float (*area)(Square* square);
};

struct Circle {
  float radius;
};

struct Triangle {
  int base;
  int height;
};

// ----------------------------------------------
void printSquare() {
  DBG("Printing square");
}

float calcSquareArea(Square* square) {
  return static_cast<float>(square->width * square->height);
}

void SquareCtor(Square* square, int w, int h) {
    (*square).width = w;
    (*square).height = h;
    (*square).print = printSquare;
    (*square).area = calcSquareArea;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: C Style 4");

  Square square;
  SquareCtor(&square, 10, 10);
  square.print();
  WRN("Square area: %.2f", square.area(&square));

  DBG("[Lesson 5]: C Style 4 [END]");
  return 0;
}

