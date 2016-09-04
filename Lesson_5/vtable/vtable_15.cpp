#include "logger.h"

// @see http://stackoverflow.com/questions/137282/how-can-i-avoid-the-diamond-of-death-when-using-multiple-inheritance
struct Base {
  virtual void foo() { INF("Base::foo()"); }
  virtual void bar() { INF("Base::bar()"); }
  void ext()         { INF("Base::ext()"); }
};

struct Derived : virtual public Base {
  void foo() override { WRN("Derived::foo()"); }
};

struct Further : virtual public Base {
  void foo() override { ERR("Further::foo()"); }
  void bar() override { ERR("Further::bar()"); }
};

struct Last : public Derived, public Further {
  void foo() override { CRT("Last::foo()"); }
};

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Vtable 15");

  Base base;
  Derived derived;
  Further further;
  Last last;

  Base* pb = &base;
  Base* pd = &derived;
  Base* pf = &further;
  Base* pl = &last;

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

  DBG("Pointer to Last");
  pl->foo();
  pl->bar();
  pl->ext();

  DBG("[Lesson 5]: Vtable 15 [END]");
  return 0;
}

