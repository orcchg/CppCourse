#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "logger.h"

#define RAND_FACTOR 5
#define NUM_PHILOS 5

bool stopped = false;

void tick() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  stopped = true;
}

/* Stick */
// ----------------------------------------------------------------------------
class Stick {
public:
  void take();
  void drop();

private:
  bool m_is_taken;
  std::condition_variable m_cond;
  std::mutex m_mutex;
};

void Stick::take() {
  std::unique_lock<std::mutex> lock(m_mutex);
  while (m_is_taken) {
    m_cond.wait(lock);
  }
  m_is_taken = true;
}

void Stick::drop() {
  std::lock_guard<std::mutex> lock(m_mutex);
  m_is_taken = false;
  m_cond.notify_all();
}

/* Philosopher */
// ----------------------------------------------------------------------------
class Philosopher {
public:
  Philosopher(int id, int factor, Stick& left, Stick& right);  // Don't copy sticks

  void run();

private:
  int m_id;
  int m_random_factor;
  Stick& m_left_stick;
  Stick& m_right_stick;

  void think();
  void eat();
};

Philosopher::Philosopher(int id, int factor, Stick& left, Stick& right)
  : m_id(id), m_random_factor(factor), m_left_stick(left), m_right_stick(right) {
  srand(m_random_factor * 119 + 1);
}

void Philosopher::run() {
  while (!stopped) {
    DBG("Philosopher[%i]: Thinking...", m_id);
    think();
    MSG("Philosopher[%i]: Trying to take left stick...", m_id);
    m_left_stick.take();
    MSG("Philosopher[%i]: Trying to take right stick...", m_id);
    m_right_stick.take();
    INF("Philosopher[%i]: Eating...", m_id);
    eat();
    m_left_stick.drop();
    m_right_stick.drop();
  }
}

// ----------------------------------------------
void Philosopher::think() {
  if (m_random_factor == 0) {
    return;
  }
  int value = rand() % 250 + 10;
  std::this_thread::sleep_for(std::chrono::milliseconds(value));
}

void Philosopher::eat() {
  think();  // some long operation
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 12]: Condition Variable 3.1");

  Stick sticks[NUM_PHILOS];
  std::vector<Philosopher> philosophers;
  for (int i = 0; i < NUM_PHILOS; ++i) {
    if (i < NUM_PHILOS - 1) {
      philosophers.emplace_back(i, RAND_FACTOR, sticks[i], sticks[i + 1]);
    } else {
      philosophers.emplace_back(i, RAND_FACTOR, sticks[0], sticks[i]);
    }
  }

  std::vector<std::thread> threads;
  threads.reserve(NUM_PHILOS);

  for (int i = 0; i < NUM_PHILOS; ++i) {
    threads.emplace_back(&Philosopher::run, philosophers[i]);
  }

  std::thread t3(tick);
  t3.detach();
  for (int i = 0; i < NUM_PHILOS; ++i) {
    threads[i].join();
  }

  DBG("[Lesson 12]: Condition Variable 3.1 [END]");
  return 0;
}

