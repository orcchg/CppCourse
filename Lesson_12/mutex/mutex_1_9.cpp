#include <mutex>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include "logger.h"

struct DivisionByZeroException {};

std::mutex mutex;

/**
 * std::unique_lock<M> implements RAII idiom on mutex resource.
 *
 * Note though that the unique_lock object does not manage 
 * the lifetime of the mutex object in any way: the duration of the mutex object 
 * shall extend at least until the destruction of the lock_guard that locks it.
 *
 * std::unique_lock<M> constructor: http://www.cplusplus.com/reference/mutex/unique_lock/unique_lock/
 *
 * See the difference between std::lock_guard<M> and std::unique_lock<M> here:
 * https://geidav.wordpress.com/2014/01/09/mutex-lock-guards-in-c11/
 */
void randomCalculate(int size, char ch) {
  try {
    std::unique_lock<std::mutex> lock(mutex, std::defer_lock);  // defer locking mutex
    lock.lock();  // enter critical section
    // TODO[Quiz]: use std::lock() instead of std::unique_lock<M>::lock() method calling
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
  } catch (DivisionByZeroException e) {  // exit critical section (dtor ~std::lock_guard<>() called)
    ERR("Exception in thread: %c", ch);
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Mutex 1.9");
  srand(239);

  std::thread t1(randomCalculate, 25, '*');
  std::thread t2(randomCalculate, 25, '$');

  t1.join();
  t2.join();

  DBG("[Lesson 12]: Mutex 1.9 [END]");
  return 0;
}

