#include <mutex>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include "logger.h"

struct DivisionByZeroException {};

std::mutex mutex_1, mutex_2;

void randomCalculate(int size, char ch) {
  try {
    std::lock(mutex_1, mutex_2);  // enter critical section
    for (int i = 0; i < size; ++i) {
      int numerator = rand() % 10;
      int denominator = rand() % 10;
      if (denominator == 0) {
        throw DivisionByZeroException();
      }
      float quotient = static_cast<float>(numerator) / denominator;
      printf(" %c%i/%i=%.2f%c ", ch, numerator, denominator, quotient, ch);
    }
    printf("\n\n");
    mutex_1.unlock();
    mutex_2.unlock();  // exit critical section
  } catch (DivisionByZeroException e) {
    ERR("Exception in thread: %c", ch);
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Mutex 1.5.1");
  srand(239);

  std::thread t1(randomCalculate, 25, '*');
  std::thread t2(randomCalculate, 25, '$');

  t1.join();
  t2.join();

  DBG("[Lesson 12]: Mutex 1.5.1 [END]");
  return 0;
}

