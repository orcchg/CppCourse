#include <algorithm>
#include <iterator>
#include <iostream>
#include "logger.h"

class Matrix {
public:
  typedef double value_type;
  typedef value_type* pointer_type;
  typedef value_type& reference_type;
  typedef pointer_type iterator;
  typedef const pointer_type const_iterator;

  Matrix(size_t size);
  Matrix(size_t size, const reference_type value);
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
  Matrix operator * (const reference_type value) const;

  Matrix& operator += (const Matrix& rhs);
  Matrix& operator -= (const Matrix& rhs);
  Matrix& operator *= (const Matrix& rhs);
  Matrix& operator *= (const reference_type value);

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

  /**
   * @defgroup Iterator Iterations on matrix elements
   * @{
   */
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  /** @} */  // end of Iterator group

private:
  size_t m_size;
  pointer_type* m_data;
};

std::ostream& operator << (std::ostream& out, const Matrix& obj);
std::istream& operator >> (std::istream& in, const Matrix& obj);

Matrix power(const Matrix& matrix, int power);

struct MatrixInversionException {
  // exception class
};


