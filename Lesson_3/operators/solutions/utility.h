#ifndef UTILITY_H_
#define UTILITY_H_

#include <limits>
#include <random>
#include "square_matrix.h"

constexpr double EPSILON = std::numeric_limits<double>::epsilon();

namespace util {

bool equals(double lhs, double rhs);

/* Generate random matrix */
// ----------------------------------------------------------------------------
class Generator {
public:
  Generator();
  virtual ~Generator();
  Matrix createInt(size_t size);
  Matrix createReal(size_t size);

private:
  std::default_random_engine m_rng;
  std::uniform_int_distribution<int> m_int_distribution;
  std::uniform_real_distribution<double> m_real_distribution;

  Matrix initFromArray(size_t size, Matrix::pointer_type* array) const;
};

}  // end namespace util

#endif  // UTILITY_H_

