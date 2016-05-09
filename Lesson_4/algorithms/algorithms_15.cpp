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

/* Anchor value */
// ----------------------------------------------------------------------------
struct AnchorValue {
  int value;
  int position;

  AnchorValue(int value, int position)
    : value(value), position(position) {
  }
};

template <typename Iter>
std::vector<AnchorValue> wrap(Iter begin, Iter end) {
  int position = 0;
  std::vector<AnchorValue> wrapped;
  while (begin != end) {
    wrapped.emplace_back(*begin++, position++);
  }
  return wrapped;
}

std::ostream& operator << (std::ostream& out, const AnchorValue& value) {
  out << "[" << value.value << ", " << value.position << "]";
  return out;
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
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 15");

  Generator generator;
  std::vector<int> array, backup;

  generate(generator, &array);
  std::copy(array.begin(), array.end(), std::back_inserter(backup));  // make a copy

  std::sort(array.begin(), array.end());
  std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<AnchorValue> wrapped = wrap(backup.begin(), backup.end());
  std::stable_sort(wrapped.begin(), wrapped.end(), std::less<AnchorValue>());
  std::copy(wrapped.begin(), wrapped.end(), std::ostream_iterator<AnchorValue>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Algorithms 15 END");
  return 0;
}

