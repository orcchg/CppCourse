#include "logger.h"

void print() {
  INF("Print: Hello, World!");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions 1");

  print();

  DBG("[Lesson 1]: Functions 1 [END]");
  return 0;
}

