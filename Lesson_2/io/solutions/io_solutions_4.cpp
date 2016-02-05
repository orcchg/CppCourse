#include <algorithm>
#include <iomanip>  // std::setprecision
#include <iostream>
#include <iterator>
#include <fstream>
#include <random>
#include <string>
#include "logger.h"

struct Matrix {
  size_t size;
  double* data;

  void init(size_t size);
  void destroy();
};

void Matrix::init(size_t sz) {
  size = sz;
  data = new double[size * size];
}

void Matrix::destroy() {
  delete [] data;
  data = nullptr;
}

std::ostream& operator << (std::ostream& out, const Matrix& matrix) {
  for (size_t i = 0; i < matrix.size; ++i) {
    for (size_t j = 0; j < matrix.size; ++j) {
      out << std::fixed << std::setprecision(5) << matrix.data[i + j] << " ";
    }
    out << "\n";
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
  std::fstream fs;
  fs.open("matrix_4.txt", std::fstream::out);
  fs << matrix;
  fs.close();
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO: Solutions 4");

  Matrix matrix;
  input(&matrix);
  output(matrix);
  matrix.destroy();

  DBG("[Lesson 2]: IO: Solutions 4 [END]");
  return 0;
}

