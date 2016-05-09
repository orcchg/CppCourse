#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include <functional>
#include <vector>
#include "logger.h"

#define COUNT 300
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

/* Anchor value */
// ----------------------------------------------
#define ID 1

struct AnchorValue {
  int value;
  int id;

  AnchorValue(int value, int id)
    : value(value), id(id) {
  }
};

template <typename Iter>
std::vector<AnchorValue> wrap(Iter begin, Iter end, int id) {
  std::vector<AnchorValue> wrapped;
  while (begin != end) {
    wrapped.emplace_back(*begin++, id);
  }
  return wrapped;
}

void printMerged(std::vector<AnchorValue>::iterator begin, std::vector<AnchorValue>::iterator end) {
  while (begin != end) {
    if (begin->id == ID) {
      printf("\e[5;00;32m%i\e[m ", begin->value);
    } else {
      printf("%i ", begin->value);
    }
    ++begin;
  }
}

// ----------------------------------------------
namespace std {

template <>
struct less<AnchorValue> {
  bool operator() (const AnchorValue& lhs, const AnchorValue& rhs) const {
    return lhs.value < rhs.value;
  }
};

}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 12");

  Generator generator;
  std::vector<int> first, second;

  generate(generator, &first);
  generator.drop();
  generate(generator, &second);

  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());

  std::vector<AnchorValue> wrap_first = wrap(first.begin(), first.end(), 0);
  std::vector<AnchorValue> wrap_second = wrap(second.begin(), second.end(), ID);
  std::vector<AnchorValue> merged;

  std::merge(wrap_first.begin(), wrap_first.end(), wrap_second.begin(), wrap_second.end(), std::back_inserter(merged), std::less<AnchorValue>());
  printMerged(merged.begin(), merged.end());

  DBG("[Lesson 4]: Algorithms 12 END");
  return 0;
}

