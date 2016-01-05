#include <algorithm>
#include <vector>
#include <cstdlib>
#include "logger.h"

/**
 * Inheritance: template base class
 */
template <typename T>
class Hasher {
public:
  virtual ~Hasher() {}

  virtual size_t hashCode() const {
    DBG("Hasher hashCode()");
    return 0;
  }

protected:
  T m_value;
};

// ----------------------------------------------
class IntHasher : public Hasher<int> {
public:
  size_t hashCode() const override {
    Hasher<int>::hashCode();
    INF("IntHasher hashCode()");
    return static_cast<size_t>(m_value % 65536);
  }
};

// ----------------------------------------------
class ShortHasher : public Hasher<short> {
public:
  size_t hashCode() const override {
    Hasher<short>::hashCode();
    WRN("ShortHasher hashCode()");
    return static_cast<size_t>(m_value);
  }
};

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Polymorphism 7");

  Hasher<int>* int_hasher = new IntHasher();
  Hasher<short>* short_hasher = new ShortHasher();

  int_hasher->hashCode();
  short_hasher->hashCode();

  DBG("[Lesson 5]: Polymorphism 7 [END]");
  return 0;
}

