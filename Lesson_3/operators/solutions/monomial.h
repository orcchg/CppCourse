#ifndef MONOMIAL_H_
#define MONOMIAL_H_

#include <iostream>
#include <limits>

constexpr double EPSILON = std::numeric_limits<double>::epsilon();

namespace util {

bool equals(double lhs, double rhs);

}  // namespace util

/* Monomial */
// ----------------------------------------------------------------------------
class Polynomial;  // declaration

class Monomial {
  friend class Polynomial;
  friend std::ostream& operator << (std::ostream& out, const Monomial& monomial);
  friend std::istream& operator >> (std::istream& in, Monomial& monomial);

public:
  typedef double value_type;

  Monomial();
  Monomial(value_type scalar);
  Monomial(int power, value_type coeff);
  Monomial(const Monomial& obj);
  virtual ~Monomial();

  inline int getPower() const { return m_power; }
  inline value_type getCoeff() const { return m_coeff; }

  /**
   * @defgroup Operators Arithmetic operations on monomials
   * @{
   */
  Monomial& operator = (Monomial rhs);

  Monomial operator + () const;
  Monomial operator - () const;

  Monomial operator * (const Monomial& rhs) const;
  Monomial operator * (value_type scalar) const;
  Monomial operator / (const Monomial& rhs) const;
  Monomial operator / (value_type scalar) const;
  Monomial& operator *= (const Monomial& rhs);
  Monomial& operator *= (value_type scalar);
  Monomial& operator /= (const Monomial& rhs);
  Monomial& operator /= (value_type scalar);

  bool operator == (const Monomial& rhs) const;
  bool operator != (const Monomial& rhs) const;

  value_type operator () (value_type value) const;
  /** @} */  // end of Operators group

  /**
   * @defgroup Maths Mathematical operations
   * @{
   */
  Monomial derivative() const;
  /** @} */  // end of Maths group

private:
  int m_power;
  value_type m_coeff;

  Monomial& operator += (const Monomial& rhs);  //!< Sum two monomials of same power only
};

std::ostream& operator << (std::ostream& out, const Monomial& monomial);
std::istream& operator >> (std::istream& in, Monomial& monomial);

/* Comparison */
// ------------------------------------------------------------------------------------------------
#include <functional>

namespace std {

/**
 * Standard compare operator specialized for Monomial objects.
 * It can be used in sorting like that: std::sort(v.begin(), v.end(), std::greater<Monomial>());
 */
template <>
struct greater<Monomial> {
  bool operator() (const Monomial& lhs, const Monomial& rhs) const {
    return lhs.getPower() > rhs.getPower();
  }
};

}

#endif  // MONOMIAL_H_

