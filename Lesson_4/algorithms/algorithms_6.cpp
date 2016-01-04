#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include <set>
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

void generate(Generator& generator, std::set<int>* out) {
  while (generator.hasNext()) {
    out->insert(generator.next());
  }
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 6");

  Generator generator;
  std::set<int> first, second;
  std::vector<int> out;

  generate(generator, &first);
  generator.drop();
  generate(generator, &second);

  std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), std::back_inserter(out));

  std::copy(out.begin(), out.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Algorithms 6 [END]");
  return 0;
}

