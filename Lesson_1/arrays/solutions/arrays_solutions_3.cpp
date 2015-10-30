#include <cstdio>
#include <cstring>
#include "logger.h"

#define SIZE 10

/* Stack */
// ----------------------------------------------------------------------------
int head1 = 0;
int stack1[SIZE];

void push1(int i) {
  if (head1 == SIZE) {
    ERR("Queue is full!");
    return;
  }

  stack1[head1++] = i;
}

int pop1() {
  if (head1 == 0) {
    ERR("Stack 1 underflow!");
    return -99999;
  }

  return stack1[--head1];
}

// ----------------------------------------------
int head2 = 0;
int stack2[SIZE];

void push2(int i) {
  DBG("PUSH 2: %i", i);
  if (head2 == SIZE) {
    ERR("Stack 2 overflow!");
    return;
  }

  stack2[head2++] = i;
}

void pop2() {
  if (head2 == 0) {
    ERR("Stack 2 underflow!");
    return;
  }

  --head2;
}

/* Queue on 2 stacks */
// ----------------------------------------------------------------------------
void enqueue(int i) {
  push1(i);
}

void dequeue() {
  if (head2 == 0) {
    if (head1 == 0) {
      ERR("Queue is empty!");
      return;
    }

    while (head1 != 0) {
      push2(pop1());
    }
  }
  pop2();
}

void printQueue() {
  for (int i = head2 - 1; i >= 0; --i) {
    printf("%i ", stack2[i]);
  }
  for (int i = 0; i < head1; ++i) {
    printf("%i ", stack1[i]);
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
    enqueue(value);
  } else if (strcmp(POP, command) == 0) {
    dequeue();
  } else if (strcmp(PRINT, command) == 0) {
    printQueue();
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
  DBG("[Lesson 1]: Arrays: Solutions 3");

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  DBG("[Lesson 1]: Arrays: Solutions 3 [END]");
  return 0;
}

