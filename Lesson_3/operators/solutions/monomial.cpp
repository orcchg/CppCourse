#include <algorithm>
#include <iomanip>
#include <cmath>
#include "monomial.h"

namespace util {

bool equals(double lhs, double rhs) {
  return std::abs(lhs - rhs) <= EPSILON;
}

}  // end namespace util

/* Monomial */
// ----------------------------------------------------------------------------
Monomial::Monomial()
  : m_power(0)
  , m_coeff(0.0) {
}

Monomial::Monomial(Monomial::value_type scalar)
  : m_power(0)
  , m_coeff(scalar) {
}

Monomial::Monomial(int power, Monomial::value_type coeff)
  : m_power(power)
  , m_coeff(coeff) {
  if (util::equals(coeff, 0.0)) {
    m_power = 0;
  }
}

Monomial::Monomial(const Monomial& obj)
  : m_power(obj.m_power)
  , m_coeff(obj.m_coeff) {
}

Monomial::~Monomial() {
}

/* Operators group */
// ------------------------------------------------------------------------------------------------
Monomial& Monomial::operator = (Monomial rhs) {
  std::swap(m_power, rhs.m_power);
  std::swap(m_coeff, rhs.m_coeff);
  return *this;
}

Monomial Monomial::operator + () const {
  return Monomial(*this);
}

Monomial Monomial::operator - () const {
  Monomial result = *this;
  result.m_coeff *= -1.0;
  return result;
}

Monomial Monomial::operator * (const Monomial& rhs) const {
  Monomial result = *this;
  result *= rhs;
  return result;
}

Monomial Monomial::operator * (Monomial::value_type scalar) const {
  Monomial result = *this;
  result *= scalar;
  return result;
}

Monomial Monomial::operator / (const Monomial& rhs) const {
  Monomial result = *this;
  result /= rhs;
  return result;
}

Monomial Monomial::operator / (Monomial::value_type scalar) const {
  Monomial result = *this;
  result /= scalar;
  return result;
}

Monomial& Monomial::operator *= (Monomial::value_type scalar) {
  m_coeff *= scalar;
  return *this;
}

Monomial& Monomial::operator *= (const Monomial& rhs) {
  m_power += rhs.m_power;
  m_coeff *= rhs.m_coeff;
}

Monomial& Monomial::operator /= (Monomial::value_type scalar) {
  m_coeff /= scalar;
  return *this;
}

Monomial& Monomial::operator /= (const Monomial& rhs) {
  m_power -= rhs.m_power;
  m_coeff /= rhs.m_coeff;
}

bool Monomial::operator == (const Monomial& rhs) const {
  return m_power == rhs.m_power && m_coeff == rhs.m_coeff;
}

bool Monomial::operator != (const Monomial& rhs) const {
  return !(*this == rhs);
}

Monomial::value_type Monomial::operator () (Monomial::value_type value) const {
  return std::pow(value, m_power) * m_coeff;
}

/* Maths group */
// ------------------------------------------------------------------------------------------------
Monomial Monomial::derivative() const {
  Monomial monomial;  // zero
  if (m_power != 0) {
    monomial.m_coeff *= monomial.m_power--;
  }
  return monomial;
}

/* Private */
// ----------------------------------------------------------------------------
Monomial& Monomial::operator += (const Monomial& rhs) {  // Quiz: why this member-function is private?
  m_coeff += rhs.m_coeff;
  return *this;
}

/* end of Operators group */
// ------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& out, const Monomial& monomial) {
  if (!util::equals(monomial.m_coeff, 0.0)) {
    out << std::setprecision(3) << monomial.m_coeff;
  } else {
    return out;
  }
  if (monomial.getPower() == 1) {
    out << "x";
  } else if (monomial.getPower() == 0) {
    // do nothing
  } else {
    out << "x^" << monomial.m_power;
  }
  return out;
}

std::istream& operator >> (std::istream& in, Monomial& monomial) {
  char x, roof;
  in >> monomial.m_coeff >> x >> roof >> monomial.m_power;
  return in;
}

