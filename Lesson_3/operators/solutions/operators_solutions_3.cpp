#include <random>
#include "square_matrix.h"

#define SIZE 3

static Matrix generate(size_t size) {
  std::default_random_engine rng;
  std::normal_distribution<double> distribution(2.0, 5.0);

  double** array = new double*[size];
  for (size_t row = 0; row < size; ++row) {
    array[row] = new double[size];
    for (size_t col = 0; col < size; ++col) {
      array[row][col] = distribution(rng);
    }
  }

  Matrix matrix(size, array);

  for (size_t row = 0; row < size; ++row) {
    delete [] array[row];
    array[row] = nullptr;
  }
  delete [] array;
  array = nullptr;

  return matrix;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Operators: Solutions 3");

  Matrix identity = Matrix::Identity(SIZE);
  Matrix identity_adjugate = Matrix(identity, 0, 0);
  std::cout << identity << std::endl;
  std::cout << identity.getTransposed() << std::endl;
  std::cout << identity.transpose() << std::endl;
  std::cout << "\nAdjugate: \n" << identity_adjugate << std::endl;
  std::cout << "\nDeterminant: " << identity.determinant() << std::endl;
  std::cout << "\nInversed: \n" << identity.getInversed() << std::endl;

  Matrix matrix = generate(SIZE);
  Matrix matrix_transposed = matrix.getTransposed();
  Matrix matrix_adjugate = Matrix(matrix, 0, 0);
  std::cout << matrix << std::endl;
  std::cout << matrix_transposed << std::endl;
  std::cout << matrix.transpose() << std::endl; 
  std::cout << std::boolalpha << (matrix == matrix_transposed) << std::endl;
  std::cout << "\nAdjugate: \n" << matrix_adjugate << std::endl;
  std::cout << "\nDeterminant: " << matrix.determinant() << std::endl;
  Matrix matrix_inversed = matrix.getInversed();
  std::cout << "\nInversed: \n" << matrix_inversed << std::endl;
  std::cout << "\nInversion check: \n" << matrix_inversed * matrix << std::endl;

  DBG("[Lesson 3]: Operators: Solutions 3 [END]");
  return 0;
}

