#include <algorithm>
#include <cstdio>
#include <cstring>
#include "logger.h"

#define SIZE 10
#define INVALID_VALUE -99999

void mpush1(int i);
int mtop1();
void mpop1();
void max_mpush1(int i);

void mpush2(int i);
int mtop2();
void mpop2();
void max_mpush2(int i);

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
  max_mpush1(i);
}

int pop1() {
  if (head1 == 0) {
    ERR("Stack 1 underflow!");
    return INVALID_VALUE;
  }

  mpop1();
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
  max_mpush2(i);
}

void pop2() {
  if (head2 == 0) {
    ERR("Queue is empty!");
    return;
  }

  --head2;
  mpop2();
}

/* Stack of maximums in Stack 1 */
// ----------------------------------------------
int mhead1 = 0;
int mstack1[SIZE];

void mpush1(int i) {
  if (mhead1 == SIZE) {
    return;
  }

  mstack1[mhead1++] = i;
}

int mtop1() {
  if (mhead1 == 0) {
    return INVALID_VALUE;
  }

  return mstack1[mhead1 - 1];
}

void mpop1() {
  if (mhead1 == 0) {
    return;
  }

  --mhead1;
}

void max_mpush1(int i) {
  if (mhead1 == 0) {
    mpush1(i);
    return;
  }

  int top = mtop1();
  if (top < i) {
    mpush1(i);
  } else {
    mpush1(top);
  }
}

/* Stack of maximums in Stack 2 */
// ----------------------------------------------
int mhead2 = 0;
int mstack2[SIZE];

void mpush2(int i) {
  if (mhead2 == SIZE) {
    return;
  }

  mstack2[mhead2++] = i;
}

int mtop2() {
  if (mhead2 == 0) {
    return INVALID_VALUE;
  }

  return mstack2[mhead2 - 1];
}

void mpop2() {
  if (mhead2 == 0) {
    return;
  }

  --mhead2;
}

void max_mpush2(int i) {
  if (mhead2 == 0) {
    mpush2(i);
    return;
  }

  int top = mtop2();
  if (top < i) {
    mpush2(i);
  } else {
    mpush2(top);
  }
}

/* Queue on 2 stacks */
// ----------------------------------------------------------------------------
void dequeue();

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

int maxInQueue() {
  int top1 = mtop1();
  int top2 = mtop2();
  return top1 > top2 ? top1 : top2;
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
    enqueue(value);
  } else if (strcmp(POP, command) == 0) {
    dequeue();
  } else if (strcmp(PRINT, command) == 0) {
    printQueue();
  } else if (strcmp(MAXIMUM, command) == 0) {
    printf("Max in queue: %i\n", maxInQueue());
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
  DBG("[Lesson 1]: Arrays: Solutions 5");

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  DBG("[Lesson 1]: Arrays: Solutions 5 [END]");
  return 0;
}

