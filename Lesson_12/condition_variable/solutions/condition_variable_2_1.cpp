#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <cstdio>
#include "logger.h"

/**
 * Make a pie:
 *
 * 1. Make a cake
 * 2. Spread with jam
 * 3. ... repeat ...
 */

bool stopped = false;

void tick() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  stopped = true;
}

/* Pie */
// ----------------------------------------------------------------------------
class Pie {
public:
  void cakeReady();
  void jamSpread();

  void waitForCakeMaking();
  void waitForJamSpreading();

private:
  bool m_cake_ready;  // TODO[Quiz]: Should we use std::atomic_bool instead ?
  std::condition_variable m_cond;
  std::mutex m_mutex;
  std::mutex m_sync_mutex;
};

// TODO[Quiz]: Why don't use std::lock_guard<M> in condition_variable ?
// @see http://stackoverflow.com/questions/13099660/c11-why-does-stdcondition-variable-use-stdunique-lock
void Pie::cakeReady() {
  std::lock_guard<std::mutex> lock(m_sync_mutex);
  m_cake_ready = true;
  m_cond.notify_all();
}

void Pie::jamSpread() {
  std::lock_guard<std::mutex> lock(m_sync_mutex);
  m_cake_ready = false;
  m_cond.notify_all();
}

void Pie::waitForCakeMaking() {
  std::unique_lock<std::mutex> lock(m_mutex);
  while (!m_cake_ready) {
    m_cond.wait(lock);
  }
}

void Pie::waitForJamSpreading() {
  std::unique_lock<std::mutex> lock(m_mutex);
  while (m_cake_ready) {
    m_cond.wait(lock);
  }
}

/* Make a Cake */
// ----------------------------------------------
void makeCake(Pie* pie) {
  while (!stopped) {
    INF("Make a cake");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // making a cake
    pie->cakeReady();
    pie->waitForJamSpreading();
  }
}

/* Spread with Jam */
// ----------------------------------------------
void spreadJam(Pie* pie) {
  while (!stopped) {
    pie->waitForCakeMaking();
    WRN("Spread with jam");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // spreading with jam
    pie->jamSpread();
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 12]: Condition Variable 2.1");

  Pie pie;

  std::thread t1(spreadJam, &pie);
  std::thread t2(makeCake, &pie);
  std::thread t3(tick);

  t3.detach();
  t1.join();
  t2.join();

  DBG("[Lesson 12]: Condition Variable 2.1 [END]");
  return 0;
}

