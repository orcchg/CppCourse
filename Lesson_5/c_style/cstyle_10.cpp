#include "logger.h"

struct Base;
struct Derived;

/* V-table */
// ----------------------------------------------
typedef void (*base_length_ptr_t)(Base*);
typedef void (*base_square_ptr_t)(Base*, int);
typedef void (*length_ptr_t)();

struct BaseVTable {
  base_length_ptr_t length_ptr;
  base_square_ptr_t square_ptr;
};

BaseVTable base_vtable;  // global

typedef void (*derived_length_ptr_t)(Derived*);
typedef void (*derived_square_ptr_t)(Derived*, int);

struct DerivedVTable {
  derived_length_ptr_t length_ptr;
  derived_square_ptr_t square_ptr;
};

DerivedVTable derived_vtable;  // global

/* Structures */
// ----------------------------------------------------------------------------
struct Base {
  void constructor();

  BaseVTable* vptr;

  int base_value;
};

void Base::constructor() {
  vptr = &base_vtable;
}

void length(Base* self) {
  ((self->vptr)->length_ptr)(self);
}

void square(Base* self, int radius) {
  ((self->vptr)->square_ptr)(self, radius);
}

// ----------------------------------------------
struct Derived {
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

void length(Derived* self) {
  ((self->vptr)->length_ptr)(self);
}

void square(Derived* self, int radius) {
  ((self->vptr)->square_ptr)(self, radius);
}

/* Table initialize */
// ----------------------------------------------
void tableInit() {
  base_vtable.length_ptr = &length;
  base_vtable.square_ptr = &square;

  derived_vtable.length_ptr = &length;
  derived_vtable.square_ptr = &square;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: C Style 10");
  tableInit();

  Base base;
  base.constructor();

  Derived derived;
  derived.constructor();

  Base* ptr_base = &base;
  length(ptr_base);

  Derived* ptr_derived = &derived;
  square(ptr_derived, 5);

  DBG("[Lesson 5]: C Style 10 [END]");
  return 0;
}

