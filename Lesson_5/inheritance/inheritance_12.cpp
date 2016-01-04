#include <algorithm>
#include <string>
#include "logger.h"

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
  Derived() { INF("Derived ctor"); }
  Derived(int base, const std::string& str) : Base(base), m_value(str) { INF("Derived(%i, %s) ctor", base, str.c_str()); }  // custom ctor
  ~Derived() { INF("Derived ~dtor"); }

  inline const std::string& getValue() const {
    return m_value;
  }

private:
  std::string m_value;
};

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 12");

  Derived first;
  Derived second(5);
  Derived third(5, "Lorem");
  
  WRN("Copy operations");
  Derived fourth = first;
  first = second;

  DBG("[Lesson 5]: Inheritance 12 [END]");
  return 0;
}
