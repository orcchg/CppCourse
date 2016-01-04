#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include <vector>
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

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 5");

  Generator generator;
  std::vector<int> first, second, out;

  generate(generator, &first);
  generator.drop();
  generate(generator, &second);

  std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), std::back_inserter(out));

  auto out_end = std::unique(out.begin(), out.end());
  std::copy(out.begin(), out_end, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Algorithms 5 [END]");
  return 0;
}

