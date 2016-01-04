#include <string>
#include "logger.h"

/**
 * Inheritance: order of ctors invocation
 */
class Base {
public:
  Base() {
    DBG("Base ctor");
  }
  ~Base() {
    ERR("Base ~dtor");
  }

  inline int getKey() const {
    return m_key;
  }

private:
  int m_key;
};

class Derived : public Base {
public:
  Derived() {
    INF("Derived ctor");
  }
  ~Derived() {
    WRN("Derived ~dtor");
  }

  inline const std::string& getValue() const {
    return m_value;
  }

private:
  std::string m_value;
};

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 1");

  Derived derived;
  derived.getKey();  // inherited method
  derived.getValue();

  DBG("[Lesson 5]: Inheritance 1 [END]");
  return 0;
}
