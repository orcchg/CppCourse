#include <string>
#include <iostream>
#include "logger.h"

class Base {
public:
  Base(int key);

  inline int getKey() const {
    return m_key;
  }

private:
  int m_key;
};

Base::Base(int key)
  : m_key(key) {
  DBG("Base ctor: %i", key);
}

// ----------------------------------------------
class Derived : public Base {
public:
  Derived(int key, const std::string& value);

  inline int getKey() const {  // overriding
    return m_key;
  }

  inline const std::string& getValue() const {
    return m_value;
  }

private:
  int m_key;  // same name field
  std::string m_value;
};

Derived::Derived(int key, const std::string& value)
  : Base(key), m_value(value) {
  INF("Derived ctor: %i %s", key, value.c_str());
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 3");

  Derived derived(5, "Lorem");
  std::cout << "Key: " << derived.getKey() << ", Value: " << derived.getValue() << std::endl;

  DBG("[Lesson 5]: Inheritance 3 [END]");
  return 0;
}

