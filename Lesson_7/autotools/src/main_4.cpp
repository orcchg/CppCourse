#include "libprint.h"
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 7]: Manual 4");

  lib::printString("Lorem ipsum");
  printValue(10);

  DBG("[Lesson 7]: Manual 4 [END]");
  return 0;
}

