#include <condition_variable>
#include <mutex>
#include <thread>
#include "logger.h"

int BIG_PIE = 1000000;

std::mutex mutex;
std::condition_variable cond;

bool stopped = false;

void tick() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  stopped = true;
}

void eat(int* part) {
  while (!stopped) {
    std::unique_lock<std::mutex> lock(mutex);
    BIG_PIE -= 100;
    *part += 100;
    cond.notify_one();
    cond.wait_for(lock, std::chrono::milliseconds(100));
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Condition Variable 1.1");

  int part_1, part_2;
  
  std::thread t1(eat, &part_1);
  std::thread t2(eat, &part_2);
  std::thread t3(tick);

  t3.detach();
  t1.join();
  t2.join();

  INF("Thread 1 ate: %i", part_1);
  INF("Thread 2 ate: %i", part_2);

  DBG("[Lesson 12]: Condition Variable 1.1 [END]");
  return 0;
}

