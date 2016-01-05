#include <iostream>
#include <string>
#include "logger.h"

/**
 * Inheritance: virtual methods from Base ctor
 */
class Base {
public:
  Base();
  virtual ~Base();

  virtual void init() = 0;
};

Base::Base() {
  DBG("Base ctor");
  init();  // virtual call in ctor
}

Base::~Base() {
}

void Base::init() {
  DBG("Base init");
}

// ----------------------------------------------
class Derived : public Base {
public:
  Derived();

  void init() override final;
};

Derived::Derived()
  : Base() {
  INF("Derived ctor");
}

void Derived::init() {
  INF("Derived init");
}

// ----------------------------------------------
class Helper : public Base {
public:
  Helper();

  void init() override final;
};

Helper::Helper()
  : Base() {
  WRN("Helper ctor");
}

void Helper::init() {
  WRN("Helper init");
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Abstract 2");

  Base* first = new Derived();
  Base* second = new Helper();

  delete first;
  delete second;

  DBG("[Lesson 5]: Abstract 2 [END]");
  return 0;
}

