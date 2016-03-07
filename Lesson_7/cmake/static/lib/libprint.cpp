#include "libprint.h"
#include "logger.h"

namespace lib {

void printString(const std::string& str) {
  DBG("Print function: %s", str.c_str());
}

}

void printValue(int value) {
  INF("Print value: %i", value);
}

