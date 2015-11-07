#include <thread>
#include <ctime>
#include "logger.h"

long long global_variable = 0;

void incrementGlobal() {
  clock_t start = clock();
  clock_t elapsed = start;
  while ((elapsed - start) < 2 * CLOCKS_PER_SEC) {
    ++global_variable;
    elapsed = clock();
  }
}

void decrementGlobal() {
  clock_t start = clock();
  clock_t elapsed = start;
  while ((elapsed - start) < 2 * CLOCKS_PER_SEC) {
    --global_variable;
    elapsed = clock();
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Threads 3.1");

  INF("Starting two threads...");
  std::thread t1(incrementGlobal);
  std::thread t2(decrementGlobal);
  INF("Main thread is freezed now");
  t1.join();
  t2.join();
  INF("Threads have finished, Main thread continues");
  WRN("Global variable is: %lli", global_variable);

  DBG("[Lesson 12]: Threads 3.1 [END]");
  return 0;
}

