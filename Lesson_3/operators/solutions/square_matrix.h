#ifndef SQUARE_MATRIX_H_
#define SQUARE_MATRIX_H_

#include <algorithm>
#include <iterator>
#include <iostream>
#include "logger.h"

class Matrix {
public:
  typedef double value_type;
  typedef value_type* pointer_type;
  typedef value_type& reference_type;

  Matrix();
  Matrix(size_t size);
  Matrix(size_t size, value_type value);
  Matrix(size_t size, pointer_type array[]);  //!< 'size' if number of rows or cols
  Matrix(const Matrix& obj);  // deep copy
  Matrix(const Matrix& obj, size_t row, size_t col);  // adjacent minor
  virtual ~Matrix();

  inline size_t size() const { return m_size; }

  /**
   * @defgroup Operators Operators on matrix
   * @{
   */
  Matrix& operator = (Matrix rhs);

  Matrix operator + () const;
  Matrix operator - () const;

  Matrix operator + (const Matrix& rhs) const;
  Matrix operator - (const Matrix& rhs) const;
  Matrix operator * (const Matrix& rhs) const;
  Matrix operator + (value_type value) const;
  Matrix operator - (value_type value) const;
  Matrix operator * (value_type value) const;

  Matrix& operator += (const Matrix& rhs);
  Matrix& operator -= (const Matrix& rhs);
  Matrix& operator *= (const Matrix& rhs);
  Matrix& operator += (value_type value);
  Matrix& operator -= (value_type value);
  Matrix& operator *= (value_type value);

  bool operator == (const Matrix& rhs) const;
  bool operator != (const Matrix& rhs) const;
  bool operator < (const Matrix& rhs) const;
  bool operator <= (const Matrix& rhs) const;
  bool operator > (const Matrix& rhs) const;
  bool operator >= (const Matrix& rhs) const;

  pointer_type operator [] (size_t row);
  const pointer_type operator [] (size_t row) const;
  reference_type operator () (size_t row, size_t col);
  value_type operator () (size_t row, size_t col) const;
  /** @} */  // end of Operators group

  /**
   * @defgroup Maths Matrix calculations
   * @{
   */
  static Matrix Identity(size_t size);  //!< Returns an Identity matrix of 'size'
  Matrix submatrix(size_t row, size_t col);  //!< Calculates adjacent minor
  Matrix& transpose();
  Matrix getTransposed() const;
  value_type determinant() const;
  value_type determinant(size_t row) const;  //!< Calculate det using specified row
  value_type trace() const;
  void diag(Matrix::pointer_type output) const;
  Matrix& inverse();
  Matrix getInversed() const;
  /** @} */  // end of Maths group

private:
  size_t m_size;
  pointer_type* m_data;
};

std::ostream& operator << (std::ostream& out, const Matrix& obj);
std::istream& operator >> (std::istream& in, Matrix& obj);

Matrix power(const Matrix& matrix, int power);

struct MatrixInversionException {
  // exception class
};

#endif  // SQUARE_MATRIX_H_

