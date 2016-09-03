#include "logger.h"

struct Base {
  virtual void foo() { INF("Base::foo()"); }
  virtual void bar() { INF("Base::bar()"); }
  void ext()         { INF("Base::ext()"); }
};

struct Derived : public Base {
  virtual void foo() override { WRN("Derived::foo()"); }

  void ext() /*hide*/ { WRN("Derived::ext()"); }
};

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Vtable 2");

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

  DBG("[Lesson 5]: Vtable 2 [END]");
  return 0;
}

