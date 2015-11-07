#include <thread>
#include "logger.h"

int fibonacci(int N) {
  int index = 1;
  int prev = 0, next = 1;

  int answer = 0;
  while (N-- > 0) {
    answer = prev + next;
    prev = next;
    next = answer;
    DBG("Fibonacci [%i]: %i", index++, answer);
  }
  return answer;  // return value is ignored
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Threads 1");

  INF("Starting thread...");
  std::thread t(fibonacci, 20);
  INF("Main thread is freezed now");
  t.join();
  INF("Thread has finished, Main thread continues");

  DBG("[Lesson 12]: Threads 1 [END]");
  return 0;
}

