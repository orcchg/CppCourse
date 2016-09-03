#include "logger.h"

struct Base;
struct Derived;

/* V-table */
// ----------------------------------------------
typedef void (Base::*base_length_ptr_t)();
typedef void (Base::*base_square_ptr_t)(int);
typedef void (*length_ptr_t)();

struct BaseVTable {
  base_length_ptr_t length_ptr;
  base_square_ptr_t square_ptr;
};

BaseVTable base_vtable;  // global

typedef void (Derived::*derived_length_ptr_t)();
typedef void (Derived::*derived_square_ptr_t)(int);

struct DerivedVTable {
  derived_length_ptr_t length_ptr;
  derived_square_ptr_t square_ptr;
};

DerivedVTable derived_vtable;  // global

/* Structures */
// ----------------------------------------------------------------------------
struct Base {
  /* virtual */ void length();
  /* virtual */ void square(int radius);

  void constructor();

  BaseVTable* vptr;

  int base_value;
};

void Base::constructor() {
  vptr = &base_vtable;
}

void Base::length() {
  DBG("Base::length()");
}

void Base::square(int) {
  DBG("Base::square()");
}

void length(Base* self) {
  //((self->vptr)->*length_ptr)(self);
}

void square(Base* self, int radius) {
  //((self->vptr)->square(self, radius);
}

// ----------------------------------------------
struct Derived {
  /* virtual */ void length();
  /* virtual */ void square(int radius);

  void constructor();

  DerivedVTable* vptr;

  /* begin Base slice */
  int base_value;
  /* end Base slice */
  int derived_value;
};

void Derived::constructor() {
  vptr = &derived_vtable;
}

void Derived::length() {
  INF("Derived::length()");
}

void Derived::square(int) {
  INF("Derived::square()");
}

void length(Derived* self) {
  //((self->vptr)->*length_ptr)(self);
}

void square(Derived* self, int radius) {
  //((self->vptr)->square(self, radius);
}

/* Table initialize */
// ----------------------------------------------
void tableInit() {
  base_vtable.length_ptr = &Base::length;
  base_vtable.square_ptr = &Base::square;

  derived_vtable.length_ptr = &Derived::length;
  derived_vtable.square_ptr = &Derived::square;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: C Style 9");
  tableInit();

  Base base;
  base.constructor();

  Derived derived;
  derived.constructor();

  Base* ptr_base = &base;
  ptr_base->length();
  length(ptr_base);

  //Base* ptr_derived = &derived;
  //ptr_derived->square();
  //square(ptr_derived);

  DBG("[Lesson 5]: C Style 9 [END]");
  return 0;
}

