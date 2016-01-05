#include <cstdio>
#include <cmath>
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
  char padding[4];  // padding

  void (*print)();
  float (*area)(Circle* square);
};

struct Triangle {
  int base;
  int height;

  void (*print)();
  float (*area)(Triangle* square);
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

// ----------------------------------------------
void printCircle() {
  DBG("Printing circle");
}

float calcCircleArea(Circle* circle) {
  return static_cast<float>(circle->radius * circle->radius * M_PI);
}

void CircleCtor(Circle* circle, float r) {
  (*circle).radius = r;
  (*circle).print = printCircle;
  (*circle).area = calcCircleArea;
}

// ----------------------------------------------
void printTriangle() {
  DBG("Printing triangle");
}

float calcTriangleArea(Triangle* triangle) {
  return static_cast<float>(triangle->base * triangle->height);
}

void TriangleCtor(Triangle* triangle, int b, int h) {
  (*triangle).base = b;
  (*triangle).height = h;
  (*triangle).print = printTriangle;
  (*triangle).area = calcTriangleArea;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: C Style 8");

  Square square;
  SquareCtor(&square, 10, 10);
  Circle circle;
  CircleCtor(&circle, 5.0f);
  Triangle triangle;
  TriangleCtor(&triangle, 2, 4);

  Shape* shapes[3];
  shapes[0] = (Shape*) &square;
  shapes[1] = (Shape*) &circle;  // Quiz: what padding should be to get Circle working ?
  shapes[2] = (Shape*) &triangle;

  for(int i = 0; i < 3; ++i) {
    shapes[i]->print();
    printf("%.2f\n", shapes[i]->area(shapes[i]));
  } 

  DBG("[Lesson 5]: C Style 8 [END]");
  return 0;
}

