#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "logger.h"

#define READERS 4

const char* getThisThreadId() {
  std::ostringstream oss;
  oss << std::this_thread::get_id();
  return oss.str().c_str();
}

/* Semaphore */
// ----------------------------------------------------------------------------
std::thread::id writer_thread_id;

class Semaphore {
public:
  Semaphore(const std::string& name)
    : m_name(name)
    , m_counter(1) {
  }

  void up() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (std::this_thread::get_id() == writer_thread_id) {
      WRN("UP: %s, thread [%s]", m_name.c_str(), getThisThreadId());
    } else {
      MSG("UP: %s, thread [%s]", m_name.c_str(), getThisThreadId());
    }
    ++m_counter;
    m_wake_up_condition.notify_one();
  }

  void down() {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (std::this_thread::get_id() == writer_thread_id) {
      WRN("DOWN: %s, counter %i, thread [%s]", m_name.c_str(), m_counter.load(), getThisThreadId());
    } else {
      MSG("DOWN: %s, counter %i, thread [%s]", m_name.c_str(), m_counter.load(), getThisThreadId());
    }
    while (m_counter.load() == 0) {
      m_wake_up_condition.wait(lock);
    }
    --m_counter;
  }

private:
  std::string m_name;
  std::atomic<int> m_counter;
  std::mutex m_mutex;
  std::condition_variable m_wake_up_condition;
};

/* Resources */
// ----------------------------------------------------------------------------
struct Resources {
  Semaphore rc_section;
  Semaphore db_section;
  int readers_count = 0;

  Resources()
    : rc_section("readers")
    , db_section("database") {
  }
};

/* Reader */
// ----------------------------------------------------------------------------
void readData() {
  INF("Data reading... Thread [%s]", getThisThreadId());
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void processData() {
  // INF("Processing read data... Thread [%s]", getThisThreadId());
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void reader(Resources* resources) {
  while (true) {
    resources->rc_section.down();
    ++resources->readers_count;
    if (resources->readers_count == 1) {
      resources->db_section.down();
    }
    resources->rc_section.up();
    readData();
    resources->rc_section.down();
    --resources->readers_count;
    if (resources->readers_count == 0) {
      resources->db_section.up();
    }
    resources->rc_section.up();
    processData();
  }
}

/* Writer */
// ----------------------------------------------------------------------------
void writeData() {
  ERR("Data writing... Thread [%s]", getThisThreadId());
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void generateData() {
  // WRN("Generating data... Thread [%s]", getThisThreadId());
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void writer(Resources* resources) {
  writer_thread_id = std::this_thread::get_id();
  while (true) {
    generateData();
    resources->db_section.down();
    writeData();
    resources->db_section.up();
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {	
  DBG("[Lesson 12]: Condition Variable 4");

  Resources resources;

  std::thread writerThread(writer, &resources);

  std::vector<std::thread> readers;
  for (int i = 0; i < READERS; ++i) {
    readers.push_back(std::thread(reader, &resources));
  }

  for (auto& readerThread : readers) {
    readerThread.join();
  }
  writerThread.join();

  DBG("[Lesson 12]: Condition Variable 4 [END]");
  return 0;
}

