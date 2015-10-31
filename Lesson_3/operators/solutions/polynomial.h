#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "monomial.h"

namespace util {

Polynomial create(
    std::default_random_engine* rng,
    std::uniform_real_distribution<double>& distribution,
    int power);  // random polynomial

}  // end namespace util

/* Polynomial */
// ----------------------------------------------------------------------------
class Polynomial {
  friend std::ostream& operator << (std::ostream& out, const Polynomial& polynomial);
  friend std::istream& operator >> (std::istream& in, Polynomial& polynomial);

public:
  typedef double value_type;

  Polynomial();
  Polynomial(const std::vector<Monomial>& monomials);
  Polynomial(const Polynomial& obj);
  virtual ~Polynomial();

  inline int getPower() const { return m_power; }

  /**
   * @defgroup Operators Arithmetic operations on polynomials
   * @{
   */
  Polynomial& operator = (Polynomial rhs);

  Polynomial operator + () const;
  Polynomial operator - () const;

  Polynomial operator + (const Monomial& rhs) const;
  Polynomial operator + (const Polynomial& rhs) const;
  Polynomial operator + (value_type scalar) const;
  Polynomial operator - (const Monomial& rhs) const;
  Polynomial operator - (const Polynomial& rhs) const;
  Polynomial operator - (value_type scalar) const;
  Polynomial operator * (const Monomial& rhs) const;
  Polynomial operator * (const Polynomial& rhs) const;
  Polynomial operator * (value_type scalar) const;
  Polynomial operator / (const Polynomial& rhs) const;
  Polynomial operator / (value_type scalar) const;
  Polynomial operator % (const Polynomial& rhs) const;

  Polynomial& operator += (const Monomial& rhs);
  Polynomial& operator += (const Polynomial& rhs);
  Polynomial& operator += (value_type scalar);
  Polynomial& operator -= (const Monomial& rhs);
  Polynomial& operator -= (const Polynomial& rhs);
  Polynomial& operator -= (value_type scalar);
  Polynomial& operator *= (const Monomial& rhs);
  Polynomial& operator *= (const Polynomial& rhs);
  Polynomial& operator *= (value_type scalar);
  Polynomial& operator /= (const Polynomial& rhs);
  Polynomial& operator /= (value_type scalar);
  Polynomial& operator %= (const Polynomial& rhs);

  bool operator == (const Polynomial& rhs) const;
  bool operator != (const Polynomial& rhs) const;

  value_type operator () (value_type value) const;
  Polynomial operator , (const Polynomial& rhs) const;  // greatest common divider
  /** @} */  // end of Operators group

  /**
   * @defgroup Maths Mathematical operations
   * @{
   */
  Polynomial derivative() const;
  /** @} */  // end of Maths group

  void print() const;  //!< Debug output

private:
  std::vector<Monomial> m_monomials;  // sorted by power in descending order
  int m_power;

  int calculatePower() const;
  void squashSamePowers();  //!< Squashes monomials with the same power into one single monomial
};

std::ostream& operator << (std::ostream& out, const Polynomial& polynomial);
std::istream& operator >> (std::istream& in, Polynomial& polynomial);

#endif  // POLYNOMIAL_H_

