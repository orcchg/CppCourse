#include <mutex>
#include <thread>
#include <vector> 
#include <cstdio>
#include "logger.h"

std::mutex mutex;

void printStar() {
  std::unique_lock<std::mutex> lock(mutex, std::defer_lock);
  // print '*' if successfully locked, 'x' otherwise: 
  if (lock.try_lock()) {
    printf("*");
  } else {
    printf("x");
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Mutex 1.10");

  std::thread t1(printStar);
  std::thread t2(printStar);
  std::thread t3(printStar);
  std::thread t4(printStar);
  std::thread t5(printStar);
  std::thread t6(printStar);
  std::thread t7(printStar);
  std::thread t8(printStar);
  std::thread t9(printStar);
  std::thread t10(printStar);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();

  DBG("[Lesson 12]: Mutex 1.10 [END]");
  return 0;
}

