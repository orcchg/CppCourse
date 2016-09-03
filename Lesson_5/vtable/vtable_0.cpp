#include "logger.h"

struct Base {
  virtual void foo() { INF("Base::foo()"); }
  virtual void bar() { INF("Base::bar()"); }
  void ext()         { INF("Base::ext()"); }
};

struct Derived : public Base {
};

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Vtable 0");

  Base base;
  Derived derived;

  Base* pb = &base;
  Base* pd = &derived;

  DBG("Pointer to Base");
  pb->foo();
  pb->bar();
  pb->ext();

  DBG("Pointer to Derived");
  pd->foo();
  pd->bar();
  pd->ext();

  DBG("[Lesson 5]: Vtable 0 [END]");
  return 0;
}

