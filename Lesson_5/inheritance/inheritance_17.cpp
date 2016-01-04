#include <string>
#include <cmath>
#include "logger.h"

// @see http://en.cppreference.com/w/cpp/language/using_declaration

/**
 * Inheritance: access to overloaded methods and overriding
 */
class Base {
public:
  Base() {}

  inline int getKey() const {
    return m_key;
  }

protected:
  int m_key;
  
  // overloading
  virtual size_t hashCode() const;
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
  
  size_t hashCode() const override;  // overriding, not hiding

private:
  std::string m_value;
};

size_t Derived::hashCode() const {
  size_t base_code = Base::hashCode();
  
  // Java String hash code: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
  int prime = 31;
  size_t hash = 0;
  int power = m_value.length() - 1;

  for (auto it = m_value.begin(); it != m_value.end(); ++it, --power) {
    hash += static_cast<size_t>(*it) * std::pow(prime, power);
  }
  
  return base_code + hash;
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 17");

  Derived derived;
  derived.getKey();  // inherited method
  derived.getValue();
  
  derived.hashCode();  // overriding of Base class implementation
  // derived.hashCode(5);
  // derived.hashCode(5, 10);
  
  std::cout << "Derived hash: " << derived.hashCode() << std::endl;  // Quiz: which version is called here?

  DBG("[Lesson 5]: Inheritance 17 [END]");
  return 0;
}
