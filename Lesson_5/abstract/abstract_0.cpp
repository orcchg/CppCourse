#include <iostream>
#include <string>
#include "logger.h"

/**
 * Inheritance: abstract class, pure virtual methods
 */
class Printable {
public:
  virtual ~Printable() {}

  virtual void print() const = 0;
};

// ----------------------------------------------
class String : public Printable {
public:
  String(const std::string& str) : m_value(str) {}

  void print() const override;

private:
  std::string m_value;
};

void String::print() const {
  DBG("String: %s", m_value.c_str());
}

// ----------------------------------------------
class Integer : public Printable {
public:
  Integer(int value) : m_value(value) {}

  void print() const override final;

private:
  int m_value;
};

void Integer::print() const {
  INF("Integer: %i", m_value);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Abstract 0");

  Printable* first = new String("Hello, World!");
  Printable* second = new Integer(10);

  first->print();
  second->print();

  delete first;
  delete second;

  DBG("[Lesson 5]: Abstract 0 [END]");
  return 0;
}

