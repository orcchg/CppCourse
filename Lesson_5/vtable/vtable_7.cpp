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

struct Further : public Derived {
  virtual void foo() override { ERR("Further::foo()"); }

  void ext() /*hide*/ { ERR("Further::ext()"); }
};

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Vtable 7");

  Base base;
  Derived derived;
  Further further;

  Base* pb = &base;
  Base* pd = &derived;
  Base* pf = &further;

  DBG("Pointer to Base");
  pb->foo();
  pb->bar();
  pb->ext();

  DBG("Pointer to Derived");
  pd->foo();
  pd->bar();
  pd->ext();

  DBG("Pointer to Further");
  pf->foo();
  pf->bar();
  pf->ext();

  DBG("[Lesson 5]: Vtable 7 [END]");
  return 0;
}

