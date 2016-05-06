#include <cstdio>
#include <cstring>
#include "logger.h"

#define SIZE 5

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
}

void pop() {
  if (head == 0) {
    ERR("Stack underflow!");
    return;
  }

  --head;
}

void printStack() {
  for (int i = 0; i < head; ++i) {
    printf("%i ", stack[i]);
  }
  printf("\n");
}

/* Interface */
// ----------------------------------------------------------------------------
const char* PUSH = "push";
const char* POP = "pop";
const char* PRINT = "print";
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
  DBG("[Lesson 1]: Arrays 8");

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  DBG("[Lesson 1]: Arrays 8 [END]");
  return 0;
}

