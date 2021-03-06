#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "logger.h"

bool stopped = false;

void tick() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  stopped = true;
}

/* Semaphore */
// ----------------------------------------------------------------------------
class Semaphore {
public:
  Semaphore(int count = 1)
    : m_counter(count) {
  }

  void up() {
    std::lock_guard<std::mutex> lock(m_mutex);
    ++m_counter;
    m_wake_up_condition.notify_one();
  }

  void down() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_counter.load() == 0) {
      m_wake_up_condition.wait(lock);
    }
    --m_counter;
  }

private:
  std::atomic<int> m_counter;
  std::mutex m_mutex;
  std::condition_variable m_wake_up_condition;
};

/* Sleeping barber */
// ----------------------------------------------------------------------------
#define CHAIRS 5

Semaphore customers_count(0);
Semaphore waiting_barbers_count(0);
std::mutex mutex;
int waiting_customers_count = 0;

void doSomething() {
  int value = rand() % 250 + 10;
  std::this_thread::sleep_for(std::chrono::milliseconds(value));
}

/* Barber */
// ----------------------------------------------
struct Barber {
  void run();
  void cutHair();
};

void Barber::run() {
  while (true) {
    customers_count.down();
    {
      std::lock_guard<std::mutex> lock(mutex);
      --waiting_customers_count;
      waiting_barbers_count.up();
    }
    cutHair();
  }
}

void Barber::cutHair() {
  INF("Cutting hair...");
  doSomething();
}

/* Customer */
// ----------------------------------------------
struct Customer {
  void run();
  void getHairCut();
};

void Customer::run() {
  std::unique_lock<std::mutex> lock(mutex);
  if (waiting_customers_count < CHAIRS) {
    ++waiting_customers_count;
    customers_count.up();
    lock.unlock();
    waiting_barbers_count.down();
    getHairCut();
  } else {
    // leave barber without having hair cut
    WRN("Left barber");
  }
}

void Customer::getHairCut() {
  DBG("Get hair cut");
  doSomething();
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 12]: Condition Variable 5");

  // TODO[Quiz]: Implement the problem.

  DBG("[Lesson 12]: Condition Variable 5 [END]");
  return 0;
}

