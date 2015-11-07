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

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Threads 0");

  INF("Starting thread...");
  std::thread t(incrementGlobal);
  INF("Main thread is freezed now");
  t.join();
  INF("Thread has finished, Main thread continues");
  WRN("Global variable is: %lli", global_variable);

  DBG("[Lesson 12]: Threads 0 [END]");
  return 0;
}

