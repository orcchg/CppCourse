#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include <vector>
#include "logger.h"

#define COUNT 50
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

/* Retain all */
// ------------------------------------------------------------------------------------------------
template <typename Forward>
void retain_all(Forward begin1, Forward end1, Forward begin2, Forward end2) {
  for (auto it = begin2; it != end2; ++it) {
    std::remove(begin1, end1, *it);
  }
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 4");

  Generator generator;
  std::vector<int> first, second;

  generate(generator, &first);
  generator.drop();
  generate(generator, &second);

  auto first_end = std::unique(first.begin(), first.end());
  auto second_end = std::unique(second.begin(), second.end());

  std::copy(first.begin(), first_end, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;	
  std::copy(second.begin(), second_end, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  retain_all(first.begin(), first_end, second.begin(), second_end);

  first_end = std::unique(first.begin(), first_end);
  std::copy(first.begin(), first_end, std::ostream_iterator<int>(std::cout, " "));

  DBG("[Lesson 4]: Algorithms 4 [END]");
  return 0;
}

