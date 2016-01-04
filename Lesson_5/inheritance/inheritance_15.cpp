#include <algorithm>
#include <string>
#include "logger.h"

/**
 * Inheritance: all inherited ctors
 */
class Base {
public:
  Base() { DBG("Base ctor"); }
  Base(int base) : m_key(base) { DBG("Base(%i) ctor", base); }  // custom ctor
  Base(const Base& obj) : m_key(obj.m_key) { DBG("Copy ctor"); }
  ~Base() { DBG("Base ~dtor"); }
  
  Base& operator = (Base rhs) {
    DBG("Assignment operator");
    std::swap(m_key, rhs.m_key);
  }

  inline int getKey() const {
    return m_key;
  }

protected:
  int m_key;
};

class Derived : public Base {
public:
  // Quiz: what ctors are inherited ?
  // Derived() { INF("Derived ctor"); }
  // ~Derived() { INF("Derived ~dtor"); }

  inline const std::string& getValue() const {
    return m_value;
  }

private:
  std::string m_value;
};

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 15");

  Derived first;
  Derived second(5);  // NOT inherited
  Derived third(5, "Lorem");  // unavailable
  
  WRN("Copy operations");
  Derived fourth = first;
  first = third;

  DBG("[Lesson 5]: Inheritance 15 [END]");
  return 0;
}
