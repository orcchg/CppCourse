#include <iomanip>
#include "square_matrix.h"
#include "utility.h"

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Operators: Solutions 3");

  Matrix identity = Matrix::Identity(SIZE);
  Matrix identity_adjugate = Matrix(identity, 0, 0);
  std::cout << "\e[5;01;31mMatrix:\e[m \n" << identity << std::endl;
  std::cout << "\e[5;00;32mTransposed:\e[m \n" << identity.getTransposed() << std::endl;
  std::cout << "\e[5;00;32mTransposed:\e[m \n" << identity.transpose() << std::endl;
  std::cout << "\e[5;00;36mMultiply by self:\e[m \n" << identity * identity << std::endl;
  std::cout << "\e[5;00;36mAdjugate:\e[m " << "det = " << identity_adjugate.determinant() << "\n" << identity_adjugate << std::endl;
  std::cout << "\e[5;00;32mDeterminant:\e[m " << identity.determinant() << std::endl;
  std::cout << "\e[5;00;33mInversed:\e[m \n" << identity.getInversed() << std::endl;

  INF("---------------------------------------------------------------------");
  util::Generator generator;

  {
    Matrix matrix = generator.createReal(SIZE);
    Matrix matrix_mul_identity = matrix * identity;
    Matrix matrix_transposed = matrix.getTransposed();
    Matrix matrix_inversed = matrix.getInversed();
    Matrix matrix_adjugate_00 = Matrix(matrix, 0, 0);
    Matrix matrix_adjugate_01 = Matrix(matrix, 0, 1);
    Matrix matrix_adjugate_02 = Matrix(matrix, 0, 2);
    Matrix matrix_adjugate_10 = Matrix(matrix, 1, 0);
    Matrix matrix_adjugate_11 = Matrix(matrix, 1, 1);
    Matrix matrix_adjugate_12 = Matrix(matrix, 1, 2);
    Matrix matrix_adjugate_20 = Matrix(matrix, 2, 0);
    Matrix matrix_adjugate_21 = Matrix(matrix, 2, 1);
    Matrix matrix_adjugate_22 = Matrix(matrix, 2, 2);
    std::cout << "\e[5;01;31mMatrix:\e[m \n" << matrix << std::endl;
    std::cout << "\e[5;00;32mTransposed:\e[m \n" << matrix_transposed << std::endl;
    std::cout << "\e[5;00;32mTransposed:\e[m \n" << matrix.transpose() << std::endl;
    std::cout << "\e[5;00;32mTranspose check:\e[m " << std::boolalpha << (matrix == matrix_transposed) << std::endl;
    matrix.transpose();  // transpose back
    std::cout << "\e[5;00;36mMultiply by identity:\e[m \n" << matrix * identity << std::endl;
    std::cout << "\e[5;00;36mMultiply by identity check:\e[m " << std::boolalpha << (matrix_mul_identity == matrix) << std::endl;
    std::cout << "\e[5;00;36mAdjugate(0, 0):\e[m " << "det = " << matrix_adjugate_00.determinant() << "\n" << matrix_adjugate_00 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(0, 1):\e[m " << "det = " << matrix_adjugate_01.determinant() << "\n" << matrix_adjugate_01 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(0, 2):\e[m " << "det = " << matrix_adjugate_02.determinant() << "\n" << matrix_adjugate_02 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(1, 0):\e[m " << "det = " << matrix_adjugate_10.determinant() << "\n" << matrix_adjugate_10 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(1, 1):\e[m " << "det = " << matrix_adjugate_11.determinant() << "\n" << matrix_adjugate_11 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(1, 2):\e[m " << "det = " << matrix_adjugate_12.determinant() << "\n" << matrix_adjugate_12 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(2, 0):\e[m " << "det = " << matrix_adjugate_20.determinant() << "\n" << matrix_adjugate_20 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(2, 1):\e[m " << "det = " << matrix_adjugate_21.determinant() << "\n" << matrix_adjugate_21 << std::endl;
    std::cout << "\e[5;00;36mAdjugate(2, 2):\e[m " << "det = " << matrix_adjugate_22.determinant() << "\n" << matrix_adjugate_22 << std::endl;
    std::cout << "\e[5;00;32mDeterminant:\e[m " << matrix.determinant() << std::endl;
    std::cout << "\e[5;00;33mInversed:\e[m \n" << matrix_inversed << std::endl;
    std::cout << "\e[5;00;33mInversion check:\e[m \n" << matrix * matrix_inversed << std::endl;
  }

  INF("---------------------------------------------------------------------");
  {
    Matrix::value_type lambda = 2.5;
    Matrix ones(SIZE, 1.0);
    Matrix matrix = generator.createInt(SIZE);
    Matrix minus_matrix = -matrix;
    std::cout << "\e[5;01;31mMatrix:\e[m \n" << matrix << std::endl;
    std::cout << "\e[5;00;36mAddition:\e[m \n" << matrix + ones << std::endl;
    std::cout << "\e[5;00;36mSubtraction:\e[m \n" << matrix - ones << std::endl;
    std::cout << "\e[5;00;36mUnary plus:\e[m: \n" << +matrix << std::endl;
    std::cout << "\e[5;00;36mUnary minus:\e[m: \n" << minus_matrix << std::endl;
    std::cout << "\e[5;00;36mMultiplication:\e[m \n" << matrix * ones << std::endl;
    std::cout << "\e[5;00;36mMultiply ones by\e[m " << lambda << ": \n" << ones * lambda << std::endl;
    std::cout << "\e[5;00;36mMultiply -ones by\e[m " << lambda << ": \n" << -ones * lambda << std::endl;
    std::cout << "\e[5;00;36mMultiply ones by\e[m " << -lambda << ": \n" << ones * -lambda << std::endl;
    std::cout << "\e[5;00;36mMultiply by\e[m " << lambda << ": \n" << matrix * lambda << std::endl;
    std::cout << "\e[5;00;32mComparison:\e[m ones < ones * lambda: " << std::boolalpha << (ones < ones * lambda) << std::endl;
    std::cout << "\e[5;00;32mComparison:\e[m ones > ones * lambda: " << std::boolalpha << (ones > ones * lambda) << std::endl;
    std::cout << "\e[5;00;32mOperator[0][0]:\e[m " << matrix[0][0] << std::endl;
    std::cout << "\e[5;00;32mOperator(0, 0):\e[m " << matrix(0, 0) << std::endl;

    std::cout << "\n\e[5;01;31mUsing [] operator:\e[m \n";
    for (size_t row = 0; row < matrix.size(); ++row) {
      for (size_t col = 0; col < matrix.size(); ++col) {
        std::cout << std::fixed << std::setprecision(4) << matrix[row][col] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n\e[5;01;31mUsing () operator:\e[m \n";
    for (size_t row = 0; row < matrix.size(); ++row) {
      for (size_t col = 0; col < matrix.size(); ++col) {
        std::cout << std::fixed << std::setprecision(4) << matrix(row, col) << " ";
      }
      std::cout << "\n";
    }

    std::cout << "\n\e[5;00;32mPower of 2:\e[m \n" << power(matrix, 2) << std::endl;
    std::cout << "\e[5;00;32mPower of -2:\e[m \n" << power(matrix, -2) << std::endl;
  }

  INF("---------------------------------------------------------------------");
  {
    Matrix input_matrix(SIZE);
    std::cout << "\e[5;00;33mInput matrix of size " << SIZE << "x" << SIZE << ":\e[m \n";
    std::cin >> input_matrix;
    std::cout << "\n\e[5;00;36mInput matrix:\e[m: \n" << input_matrix << std::endl;
    std::cout << "\e[5;00;33mInversed:\e[m \n" << input_matrix.inverse() << std::endl;
  }

  DBG("[Lesson 3]: Operators: Solutions 3 [END]");
  return 0;
}

