#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdio>
#include "logger.h"

#define COUNT 1000
#define STOP -1

/* Generator */
// ------------------------------------------------------------------------------------------------
class Generator {
public:
  Generator();

  inline bool hasNext() const {
    return m_count <= COUNT;
  }

  inline int next() {
    if (m_count > COUNT) {
      return STOP;
    }
    ++m_count;
    return m_distribution(m_rng);
  }

  inline void drop() { m_count = 0; }

private:
  std::default_random_engine m_rng;
  std::uniform_int_distribution<int> m_distribution;
  int m_count;
};

Generator::Generator()
  : m_rng()
  , m_distribution(0, 100)
  , m_count(0) {
}

void generate(Generator& generator, std::vector<int>* out) {
  out->reserve(COUNT * 2);
  while (generator.hasNext()) {
    out->push_back(generator.next());
  }
}

template <typename Iter>
void printRange(Iter begin, Iter end, Iter first, Iter second) {
  while (begin != end) {
    if (begin >= first && begin < second) {
      printf("\e[5;00;33m%i\e[m ", *begin);
    } else {
      printf("%i ", *begin);
    }
    ++begin;
  }
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 10");

  Generator generator;
  std::vector<int> values;

  generate(generator, &values);  // Quiz: shall already be sorted

  std::pair<std::vector<int>::iterator, std::vector<int>::iterator> bounds;
  int value = 50;

  do {
    bounds = std::equal_range(values.begin(), values.end(), value);
    ++value;
  } while (bounds.second - bounds.first == 0 && value <= 100);

  INF("Value of equal range: %i", value);
  printRange(values.begin(), values.end(), bounds.first, bounds.second);

  DBG("[Lesson 4]: Algorithms 10 END");
  return 0;
}

