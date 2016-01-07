#include <string>
#include "logger.h"
#include "symbol_table.h"

namespace lib {

extern void (*printString)(const std::string& str);

}

extern void (*printValue)(int value);

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 7]: Manual 2");

  SymbolTable symbolTable;
  bool success = symbolTable.loadLibrary("libprint.so");
  if (!success) {
    ERR("Library not loaded");
  }

  //lib::printString("Lorem ipsum");
  printValue(10);

  DBG("[Lesson 7]: Manual 2 [END]");
  return 0;
}

