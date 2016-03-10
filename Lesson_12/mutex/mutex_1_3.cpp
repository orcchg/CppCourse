#include <mutex>
#include <thread>
#include <cstdio>
#include "logger.h"

std::mutex mutex;

void print(int size, char ch) {
  mutex.lock();  // enter critical section
  for (int i = 0; i < size; ++i) {
    printf("%c", ch);
  }
  printf("\n");
  mutex.unlock();  // exit critical section
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Mutex 1.3");

  std::thread t1(print, 25, '*');
  std::thread t2(print, 25, '$');

  t1.join();
  t2.join();

  DBG("[Lesson 12]: Mutex 1.3 [END]");
  return 0;
}

