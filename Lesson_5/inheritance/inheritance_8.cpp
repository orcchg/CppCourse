#include <string>
#include "logger.h"

// @see http://en.cppreference.com/w/cpp/language/using_declaration

class Base {
public:
  Base() {}

  inline int getKey() const {
    return m_key;
  }

protected:
  int m_key;
  
  // overloading
  size_t hashCode() const;
  size_t hashCode(int base) const;
  size_t hashCode(int base, int addon) const;
};

size_t Base::hashCode() const {
  return static_cast<size_t>(m_key);
}

size_t Base::hashCode(int base) const {
  return base + hashCode();
}

size_t Base::hashCode(int base, int addon) const {
  return base * hashCode() + addon;
}

// ----------------------------------------------
class Derived : public Base {
public:
  Derived() {}

  inline const std::string& getValue() const {
    return m_value;
  }
  
  using Base::hashCode;  // introduces all inherited overloaded Base methods as 'public' in Derived

private:
  std::string m_value;
};

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 8");

  Derived derived;
  derived.getKey();  // inherited method
  derived.getValue();
  
  // protected methods - made visible in Derived class
  derived.hashCode();
  derived.hashCode(5);
  derived.hashCode(5, 10);
  
  std::cout << "Derived hash: " << derived.hashCode() << std::endl;

  DBG("[Lesson 5]: Inheritance 8 [END]");
  return 0;
}
