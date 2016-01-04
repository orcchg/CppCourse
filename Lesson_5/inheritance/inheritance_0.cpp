#include <string>
#include "logger.h"

/**
 * Inheritance syntax
 */
class Base {
public:
  Base() {}

  inline int getKey() const {
    return m_key;
  }

private:
  int m_key;
};

class Derived : public Base {
public:
  Derived() {}

  inline const std::string& getValue() const {
    return m_value;
  }

private:
  std::string m_value;
};

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 0");

  Base base;
  base.getKey();

  Derived derived;
  derived.getKey();  // inherited method
  derived.getValue();

  DBG("[Lesson 5]: Inheritance 0 [END]");
  return 0;
}

