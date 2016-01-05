#include <string>
#include "logger.h"

/**
 * Inheritance: in pure C
 */
struct Base {
  int key;

  int getKey();
};

int Base::getKey() {
  return key;
}

// ----------------------------------------------
struct Derived {
  Base super;  // composition
  std::string value;

  int getKey();
  std::string& getValue();
};

int Derived::getKey() {  // 'inherited' method
  return super.getKey();
}

std::string& Derived::getValue() {
  return value;
}

// ----------------------------------------------
size_t hash(Base* ptr) {
  return static_cast<size_t>(ptr->getKey());
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: C Style 1");

  Derived derived;
  hash(&(derived.super));

  DBG("[Lesson 5]: C Style 1 [END]");
  return 0;
}

