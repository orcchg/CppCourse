#include <cstdio>
#include <cstring>
#include "logger.h"

#define SIZE 5
#define INVALID_VALUE -99999

void mpush(int i);
int mtop();
void mpop();
void max_mpush(int i);

/* Stack */
// ----------------------------------------------------------------------------
int head = 0;
int stack[SIZE];

void push(int i) {
  if (head == SIZE) {
    ERR("Stack overflow!");
    return;
  }

  stack[head++] = i;
  max_mpush(i);
}

void pop() {
  if (head == 0) {
    ERR("Stack underflow!");
    return;
  }

  --head;
  mpop();
}

void printStack() {
  for (int i = 0; i < head; ++i) {
    printf("%i ", stack[i]);
  }
  printf("\n");
}

int maxInStack() {
  return mtop();
}

/* Stack of maximums */
// ----------------------------------------------
int mhead = 0;
int mstack[SIZE];

void mpush(int i) {
  if (mhead == SIZE) {
    ERR("Stack M overflow!");
    return;
  }

  mstack[mhead++] = i;
}

int mtop() {
  if (mhead == 0) {
    ERR("Stack underflow!");  // intentionally omitted 'M'
    return INVALID_VALUE;
  }

  return mstack[mhead - 1];
}

void mpop() {
  if (mhead == 0) {
    ERR("Stack M underflow!");
    return;
  }

  --mhead;
}

void max_mpush(int i) {
  if (mhead == 0) {
    mpush(i);
    return;
  }

  int top = mtop();
  if (top < i) {
    mpush(i);
  } else {
    mpush(top);
  }
}

/* Interface */
// ----------------------------------------------------------------------------
const char* PUSH = "push";
const char* POP = "pop";
const char* PRINT = "print";
const char* MAXIMUM = "max";
const char* EXIT = "exit";

bool evaluate(char* command) {
  if (strcmp(PUSH, command) == 0) {
    int value = 0;
    printf("value = ");
    scanf("%i", &value);
    push(value);
  } else if (strcmp(POP, command) == 0) {
    pop();
  } else if (strcmp(PRINT, command) == 0) {
    printStack();
  } else if (strcmp(MAXIMUM, command) == 0) {
    printf("Max in stack: %i\n", maxInStack());
  } else if (strcmp(EXIT, command) == 0) {
    return false;
  } else {
    WRN("Undefined command: %s", command);
  }
  return true;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays: Solutions 4");

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  DBG("[Lesson 1]: Arrays: Solutions 4 [END]");
  return 0;
}

