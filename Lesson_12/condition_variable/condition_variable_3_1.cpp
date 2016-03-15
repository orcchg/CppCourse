#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "logger.h"

#define NUM_PHILOS 5

bool stopped = false;

void tick() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  stopped = true;
}

/* Global mutex */
// ----------------------------------------------------------------------------
std::mutex mutex;
std::mutex philosopher_lock[NUM_PHILOS];
std::condition_variable semaphore;

/* Philosopher */
// ----------------------------------------------------------------------------
enum class State : int {
  HUNGRY = 0, THINKING = 1, EATING = 2
};

State states[NUM_PHILOS];

int getLeftId(int id) {
  int left_id = (id + NUM_PHILOS - 1) % NUM_PHILOS;
  return left_id;
}

int getRightId(int id) {
  int right_id = (id + 1) % NUM_PHILOS;
  return right_id;
}

// ----------------------------------------------
class Philosopher {
public:
  Philosopher(int id);

  void run();

private:
  int m_id;

  void think();
  void eat();

  void tryToEat();
  void dropSticks();

  void tryTakeSticks(int id);
};

Philosopher::Philosopher(int id)
  : m_id(id) {
}

void Philosopher::run() {
  while (!stopped) {
    DBG("Philosopher[%i]: Thinking...", m_id);
    think();
    MSG("Philosopher[%i]: Trying to take both sticks...", m_id);
    tryToEat();
    INF("Philosopher[%i]: Eating...", m_id);
    eat();
    dropSticks();
  }
}

void Philosopher::tryToEat() {
  {  // enter Critical section
    std::lock_guard<std::mutex> lock(mutex);
    states[m_id] = State::HUNGRY;
    tryTakeSticks(m_id);  // start eat or fall back to wait
  }  // exit Critical section
  std::unique_lock<std::mutex> lock(philosopher_lock[m_id], std::defer_lock);
  semaphore.wait(lock);
}

void Philosopher::dropSticks() {
  std::lock_guard<std::mutex> lock(mutex);
  states[m_id] = State::THINKING;
  tryTakeSticks(getLeftId(m_id));
  tryTakeSticks(getRightId(m_id));
}

void Philosopher::tryTakeSticks(int id) {
  if (states[id] == State::HUNGRY && states[getLeftId(id)] != State::EATING && states[getRightId(id)] != State::EATING) {
    states[id] = State::EATING;
    semaphore.notify_one();
  }
}

// ----------------------------------------------
void Philosopher::think() {
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

  std::vector<Philosopher> philosophers;
  for (int i = 0; i < NUM_PHILOS; ++i) {
    philosophers.emplace_back(i);
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

