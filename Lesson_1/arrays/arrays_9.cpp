#include <algorithm>
#include <cstdio>
#include <cstring>
#include "logger.h"

/* Queue */
// ----------------------------------------------------------------------------
int head = 0;
int tail = 0;
int queue[SIZE];
int copy[SIZE];

static void reallocate() {
  for (int i = head; i < tail; ++i) {
    copy[i - head] = queue[i];
  }
  tail -= head;
  head = 0;
  std::swap(copy, queue);
}

void enqueue(int i) {
  if (tail == SIZE) {
    ERR("Queue is full!");
    return;
  }

  queue[tail++] = i;
}

void dequeue() {
  if (head == tail) {
    ERR("Queue is empty!");
    return;
  }

  ++head;
  reallocate();
}

void printQueue() {
  for (int i = head; i < tail; ++i) {
    printf("%i ", queue[i]);
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
  DBG("[Lesson 1]: Arrays 9");

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  DBG("[Lesson 1]: Arrays 9 [END]");
  return 0;
}

