#include <chrono>
#include <thread>
#include <cstdio>
#include "logger.h"

void print(int size, char ch) {
  for (int i = 0; i < size; ++i) {
    printf("%c", ch);
    std::this_thread::yield();
  }
  printf("\n");
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Mutex 1");

  std::thread t1(print, 25, '*');
  std::thread t2(print, 25, '$');

  t1.join();
  t2.join();

  DBG("[Lesson 12]: Mutex 1 [END]");
  return 0;
}

