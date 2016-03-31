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
  while (!stopped) {
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
const int NUM_CUSTOMERS = 10;

int main(int argc, char** argv) {
  DBG("[Lesson 12]: Condition Variable 5.1");

  Barber barber;
  std::thread barber_t(&Barber::run, barber);

  std::vector<Customer> customers(NUM_CUSTOMERS);
  std::vector<std::thread> customers_t;
  for (int i = 0; i < NUM_CUSTOMERS; ++i) {
    customers_t.emplace_back(&Customer::run, customers[i]);
  }

  std::thread t3(tick);
  t3.detach();
  for (int i = 0; i < NUM_CUSTOMERS; ++i) {
    customers_t[i].join();
  }
  barber_t.join();

  DBG("[Lesson 12]: Condition Variable 5.1 [END]");
  return 0;
}

