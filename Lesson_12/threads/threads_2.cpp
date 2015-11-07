#include <chrono>
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
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
  WRN("Thread has finished");
  return answer;  // return value is ignored
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Threads 2");

  INF("Starting thread...");
  std::thread t(fibonacci, 20);
  INF("Detaching thread");
  t.detach();
  INF("Main thread continues");
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  WRN("Main thread has finished: destroying all local objects");

  DBG("[Lesson 12]: Threads 2 [END]");
  return 0;
}

