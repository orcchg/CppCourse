#include <cstdio>
#include "logger.h"

// @see http://www.codeproject.com/Articles/739687/Achieving-polymorphism-in-C

/**
 * Inheritance: polymorphism in pure C
 */
struct Shape {
  char padding[8];  // padding technique
  void (*print)();
  float (*area)(Shape* square);
};

// ----------------------------------------------
struct Square {
  int width;
  int height;

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
  DBG("[Lesson 5]: C Style 6");

  Square square;
  SquareCtor(&square, 10, 10);
  square.print();
  WRN("Square area: %.2f", square.area(&square));

  /**
   * What we want to happen is that the print() activation of the Shape pointer 
   * will activate the print() function of the Square object which its pointing to.
   */
  Shape* ptr = reinterpret_cast<Shape*>(&square);
  ptr->print();  // expected polymorphism

  DBG("[Lesson 5]: C Style 6 [END]");
  return 0;
}

