#include <atomic>
#include <thread>
#include <vector>
#include "logger.h"

#define BUFFER_SIZE 1000
#define NUM_THREADS 4

/* Generator */
// ----------------------------------------------------------------------------
class IntGenerator {
public:
  IntGenerator();
  virtual ~IntGenerator();

  virtual int next() = 0;

  inline void cancel() { m_is_canceled = true; }
  inline bool isCanceled() const { return m_is_canceled; }

private:
  volatile bool m_is_canceled;
};

IntGenerator::IntGenerator()
  : m_is_canceled(false) {
}

IntGenerator::~IntGenerator() {
}

// ----------------------------------------------
class UniqueNumberGenerator : public IntGenerator {
public:
  static const int neverValue = -1;
  static const int startValue = 0;

  UniqueNumberGenerator();
  virtual ~UniqueNumberGenerator();

  int next() override final;

private:
  std::atomic<int> m_unique_number;
};

UniqueNumberGenerator::UniqueNumberGenerator()
  : IntGenerator()
  , m_unique_number(startValue) {
}

UniqueNumberGenerator::~UniqueNumberGenerator() {
}

int UniqueNumberGenerator::next() {
  return m_unique_number++;  // Atomic operation now
}

/* Circular buffer */
// ----------------------------------------------------------------------------
class CircularBuffer {
public:
  CircularBuffer(size_t size);
  virtual ~CircularBuffer();

  void add(int value);
  bool contains(int value);

private:
  size_t m_size;
  int m_offset;
  int* m_array;
};

CircularBuffer::CircularBuffer(size_t size)
  : m_size(size)
  , m_offset(0)
  , m_array(new int[size]) {
  for (size_t i = 0; i < size; ++i) {
    m_array[i] = UniqueNumberGenerator::neverValue;
  }
}

CircularBuffer::~CircularBuffer() {
  delete [] m_array;
  m_array = nullptr;
}

void CircularBuffer::add(int value) {
  m_array[m_offset++] = value;
  m_offset %= m_size;  // rollback, rewriting old values
}

bool CircularBuffer::contains(int value) {
  for (size_t i = 0; i < m_size; ++i) {
    if (m_array[i] == value) {
      return true;
    }
  }
  return false;
}

/* Checker */
//-----------------------------------------------------------------------------
class Checker {
public:
  virtual ~Checker();
  static void test(IntGenerator* generator, CircularBuffer* buffer);

private:
  IntGenerator* m_generator;
  CircularBuffer* m_buffer;
  int m_id;

  Checker(IntGenerator* generator, CircularBuffer* buffer, int id);
  void run();  // worker thread method
};

Checker::Checker(IntGenerator* generator, CircularBuffer* buffer, int id)
  : m_generator(generator)
  , m_buffer(buffer)
  , m_id(id) {
}

Checker::~Checker() {
  m_generator = nullptr;
}

void Checker::run() {
  while (!m_generator->isCanceled()) {  // TODO: provide Timer to leave in N seconds
    int unique_number = m_generator->next();
    if (m_buffer->contains(unique_number)) {
      ERR("ID [%i]: Duplicate value detected! %i", m_id, unique_number);
      m_generator->cancel();
    }
    m_buffer->add(unique_number);
  }
}

void Checker::test(IntGenerator* generator, CircularBuffer* buffer) {
  std::vector<std::thread> threads;
  threads.reserve(NUM_THREADS);

  for (size_t i = 0; i < NUM_THREADS; ++i) {
    Checker checker(generator, buffer, i);
    threads.emplace_back(&Checker::run, checker);
  }
  for (auto& t : threads) {
    t.join();
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 12]: Atomic 1");

  UniqueNumberGenerator generator;
  CircularBuffer buffer(BUFFER_SIZE);
  Checker::test(&generator, &buffer);

  DBG("[Lesson 12]: Atomic 1 [END]");
  return 0;
}

