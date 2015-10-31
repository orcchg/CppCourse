#include <cmath>
#include "utility.h"

namespace util {

bool equals(double lhs, double rhs) {
  return std::abs(lhs - rhs) <= EPSILON;
}

/* Generate random matrix */
// ----------------------------------------------------------------------------
Generator::Generator()
  : m_rng()
  , m_int_distribution(0, 9)
  , m_real_distribution(-1.0, 1.0) {
}

Generator::~Generator() {
}

Matrix Generator::createInt(size_t size) {
  double** array = new double*[size];
  for (size_t row = 0; row < size; ++row) {
    array[row] = new double[size];
    for (size_t col = 0; col < size; ++col) {
      array[row][col] = m_int_distribution(m_rng);
    }
  }
  return initFromArray(size, array);
}

Matrix Generator::createReal(size_t size) {
  double** array = new double*[size];
  for (size_t row = 0; row < size; ++row) {
    array[row] = new double[size];
    for (size_t col = 0; col < size; ++col) {
      array[row][col] = m_real_distribution(m_rng);
    }
  }
  return initFromArray(size, array);
}

Matrix Generator::initFromArray(size_t size, Matrix::pointer_type* array) const {
  Matrix matrix(size, array);

  for (size_t row = 0; row < size; ++row) {
    delete [] array[row];
    array[row] = nullptr;
  }
  delete [] array;
  array = nullptr;

  return matrix;
}

}  // end namespace util

