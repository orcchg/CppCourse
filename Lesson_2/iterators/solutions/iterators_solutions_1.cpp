#include <algorithm>
#include <iomanip>  // std::setprecision
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include "logger.h"

struct Matrix {
  typedef double* iterator;

  size_t size;
  double* data;

  void init(size_t size);
  void destroy();

  iterator begin() const;
  iterator end() const;
};

void Matrix::init(size_t sz) {
  size = sz;
  data = new double[size * size];
}

void Matrix::destroy() {
  delete [] data;
  data = nullptr;
}

Matrix::iterator Matrix::begin() const {
  return data;
}

Matrix::iterator Matrix::end() const {
  return data + size * size;
}

std::ostream& operator << (std::ostream& out, const Matrix& matrix) {
  for (Matrix::iterator it = matrix.begin(); it != matrix.end(); ++it) {
    if ((it - matrix.begin()) % matrix.size == 0) {
      out << "\n";
    }
    out << std::fixed << std::setprecision(5) << *it << " ";
  }
  out << std::endl;
  return out;
}

/* Utility */
// ----------------------------------------------------------------------------
int generate(Matrix* matrix) {
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  size_t size = matrix->size;
  std::cout << "Генерируется случайная матрица " << size << "х" << size << std::endl;
  size *= size;

  for (size_t i = 0; i < size; ++i) {
    matrix->data[i] = distribution(generator);
  }
}

/* I/O */
// ----------------------------------------------------------------------------
void input(Matrix* matrix) {
  size_t size = 0;
  std::cout << "Введите размер матрицы: ";
  std::cin >> size;
  matrix->init(size);
  generate(matrix);
}

void output(const Matrix& matrix) {
  std::cout << matrix << std::endl;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: Iterators: Solutions 1");

  Matrix matrix;
  input(&matrix);
  output(matrix);
  matrix.destroy();

  DBG("[Lesson 2]: Iterators: Solutions 1 [END]");
  return 0;
}

