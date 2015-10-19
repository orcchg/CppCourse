#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>
#include "logger.h"

#define SIZE 10

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

/* Queue */
// ----------------------------------------------------------------------------
int qhead = 0;
int tail = 0;
int queue[SIZE];
int copy[SIZE];

static void reallocate() {
  for (int i = qhead; i < tail; ++i) {
    copy[i - qhead] = queue[i];
  }
  tail -= qhead;
  qhead = 0;
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
  if (qhead == tail) {
    ERR("Queue is empty!");
    return;
  }

  ++qhead;
  reallocate();
}

/* Unit test */
// ----------------------------------------------------------------------------
bool equalContent(std::stack<int>& std_stack) {
  while (!std_stack.empty()) {
    int top = std_stack.top();
    if (stack[head - 1] != top) {
      ERR("Stack: expected = %i, actual = %i", top, stack[head - 1]);
      return false;
    }
    std_stack.pop();
    pop();
  }
  return head == 0;
}

bool equalContent(std::queue<int>& std_queue) {
  while (!std_queue.empty()) {
    int front = std_queue.front();
    if (queue[qhead] != front) {
      ERR("Queue: expected = %i, actual = %i", front, queue[qhead]);
      return false;
    }
    std_queue.pop();
    dequeue();
  }
  return qhead == tail;
}

enum Command {
  PUSH = 0, POP = 1, ENQUEUE = 2, DEQUEUE = 3
};

void unitTest() {
  std::stack<int> std_stack;
  std::queue<int> std_queue;

  clock_t start = clock();
  clock_t elapsed = start;

  int pushes = 0, pops = 0, enqs = 0, deqs = 0;

  while ((elapsed - start) < 1 * CLOCKS_PER_SEC) {
    int value = rand() % 100;

    Command command = static_cast<Command>(rand() % 4);
    switch (command) {
      case Command::PUSH:
        if (head != SIZE) {
          std_stack.push(value);
          push(value);
          ++pushes;
        }
        break;
      case Command::POP:
        if (!std_stack.empty()) {
          std_stack.pop();
          pop();
          ++pops;
        }
        break;
      case Command::ENQUEUE:
       if (tail != SIZE) {
          std_queue.push(value);
          enqueue(value);
          ++enqs;
        }
        break;
      case Command::DEQUEUE:
        if (!std_queue.empty()) {
          std_queue.pop();
          dequeue();
          ++deqs;
        }
        break;
    }
    int total = rand() % 8 + 4;
    if ((pushes % total == 0 && !equalContent(std_stack)) ||
        (enqs % total == 0 && !equalContent(std_queue))) {
      return;
    }
    INF("OK");
    elapsed = clock();
  }
  INF("OK: pushes = %i, pops = %i, enqs = %i, deqs = %i", pushes, pops, enqs, deqs);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays: Solutions 1");
  unitTest();
  DBG("[Lesson 1]: Arrays: Solutions 1 [END]");
  return 0;
}

