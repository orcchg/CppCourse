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
  bool m_jam_spread;  // TODO[Quiz]: Should we use std::atomic_bool instead ?
  std::condition_variable m_cond;
  std::mutex m_mutex;
};

void Pie::cakeReady() {

}

void Pie::jamSpread() {

}

void Pie::waitForCakeMaking() {

}

void Pie::waitForJamSpreading() {

}

/* Make a Cake */
// ----------------------------------------------
void makeCake(Pie* pie) {
  while (!stopped) {
    INF("Make a cake");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));  // making a cake
    pie->cakeReady();
    pie->waitForJamSpreading();
  }
}

/* Spread with Jam */
// ----------------------------------------------
void spreadJam(Pie* pie) {
  while (!stopped) {
    pie->waitForJamSpreading();
    WRN("Spread with jam");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));  // spreading with jam
    pie->jamSpread();
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 12]: Condition Variable 2");

  Pie pie;

  std::thread t1(spreadJam, &pie);
  std::thread t2(makeCake, &pie);
  std::thread t3(tick);

  t3.detach();
  t1.join();
  t2.join();

  DBG("[Lesson 12]: Condition Variable 2 [END]");
  return 0;
}

