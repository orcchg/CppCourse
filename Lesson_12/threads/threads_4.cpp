#include <thread>
#include <vector>
#include "logger.h"

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
class EvenIntGenerator : public IntGenerator {
public:
  EvenIntGenerator();
  virtual ~EvenIntGenerator();

  int next() override final;

private:
  int m_current_even_value;
};

EvenIntGenerator::EvenIntGenerator()
  : IntGenerator()
  , m_current_even_value(0) {
}

EvenIntGenerator::~EvenIntGenerator() {
}

int EvenIntGenerator::next() {
  ++m_current_even_value;  // Dangerous point !!!
  ++m_current_even_value;
  return m_current_even_value;
}

/* Checker */
// ----------------------------------------------------------------------------
class Checker {
public:
  virtual ~Checker();
  static void test(IntGenerator* generator);

private:
  IntGenerator* m_generator;
  int m_id;

  Checker(IntGenerator* generator, int id);
  void run();  // worker thread method
};

Checker::Checker(IntGenerator* generator, int id)
  : m_generator(generator)
  , m_id(id) {
}

Checker::~Checker() {
  m_generator = nullptr;
}

void Checker::run() {
  while (!m_generator->isCanceled()) {
    int value = m_generator->next();
    if (value % 2 != 0) {
      ERR("ID [%i]: Odd value detected! %i", m_id, value);
      m_generator->cancel();
    }
  }
}

void Checker::test(IntGenerator* generator) {
  std::vector<std::thread> threads;
  threads.reserve(NUM_THREADS);

  for (size_t i = 0; i < NUM_THREADS; ++i) {
    Checker checker(generator, i);
    threads.emplace_back(&Checker::run, checker);
  }
  for (auto& t : threads) {
    t.join();
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 12]: Threads 4");

  EvenIntGenerator generator;
  Checker::test(&generator);

  DBG("[Lesson 12]: Threads 4 [END]");
  return 0;
}

