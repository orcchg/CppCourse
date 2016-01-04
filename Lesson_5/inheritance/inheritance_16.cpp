#include <algorithm>
#include <string>
#include "logger.h"

/**
 * Inheritance: default ctor is disabled by custom one
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
  using Base::Base;
  
  // custom ctor disables default one
  Derived(int base, const std::string& str) : Base(base), m_value(str) { INF("Derived(%i, %s) ctor", base, str.c_str()); }

  inline const std::string& getValue() const {
    return m_value;
  }

private:
  std::string m_value;
};

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 16");

  // Derived first;  // disabled
  Derived second(5);  // inherited now
  Derived third(5, "Lorem");
  
  WRN("Copy operations");
  Derived fourth = second;
  second = third;

  DBG("[Lesson 5]: Inheritance 16 [END]");
  return 0;
}
