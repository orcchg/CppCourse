#include <functional>
#include <string>
#include <sstream>
#include "polynomial.h"

namespace util {

Polynomial create(
    std::default_random_engine* rng,
    std::uniform_real_distribution<double>& distribution,
    int power) {
  std::vector<Monomial> monomials;
  for (int i = 0; i < power; ++i) {
    auto value = distribution(*rng);
    monomials.emplace_back(power - i - 1, value);
  }
  return Polynomial(monomials);
}

}  // end namespace util

/* Polynomial */
// ------------------------------------------------------------------------------------------------
Polynomial::Polynomial()
  : m_monomials()
  , m_power(0) {
}

Polynomial::Polynomial(const std::vector<Monomial>& monomials)
  : m_monomials(monomials)
  , m_power(calculatePower()) {
  std::sort(m_monomials.begin(), m_monomials.end(), std::greater<Monomial>());  // sort by power in descending order
}

Polynomial::Polynomial(const Polynomial& obj)
  : m_monomials(obj.m_monomials)
  , m_power(obj.m_power) {
}

Polynomial::~Polynomial() {
  m_monomials.clear();
  m_power = 0;
}

/* Operators group */
// ------------------------------------------------------------------------------------------------
Polynomial& Polynomial::operator = (Polynomial rhs) {
  std::swap(m_monomials, rhs.m_monomials);
  std::swap(m_power, rhs.m_power);
  return *this;
}

Polynomial Polynomial::operator + () const {
  return Polynomial(*this);
}

Polynomial Polynomial::operator - () const {
  Polynomial result = *this;
  for (size_t i = 0; i < result.m_monomials.size(); ++i) {
    result.m_monomials[i] *= -1.0;
  }
  return result;
}

Polynomial Polynomial::operator + (const Monomial& rhs) const {
  Polynomial result = *this;
  result += rhs;
  return result;
}

Polynomial Polynomial::operator + (const Polynomial& rhs) const {
  Polynomial result = *this;
  result += rhs;
  return result;
}

Polynomial Polynomial::operator + (Polynomial::value_type scalar) const {
  Polynomial result = *this;
  result += scalar;
  return result;
}

Polynomial Polynomial::operator - (const Monomial& rhs) const {
  Polynomial result = *this;
  result -= rhs;
  return result;
}

Polynomial Polynomial::operator - (const Polynomial& rhs) const {
  Polynomial result = *this;
  result -= rhs;
  return result;
}

Polynomial Polynomial::operator - (Polynomial::value_type scalar) const {
  Polynomial result = *this;
  result -= scalar;
  return result;
}

Polynomial Polynomial::operator * (const Monomial& rhs) const {
  Polynomial result = *this;
  result *= rhs;
  return result;
}

Polynomial Polynomial::operator * (const Polynomial& rhs) const {
  Polynomial result = *this;
  result *= rhs;
  return result;
}

Polynomial Polynomial::operator * (Polynomial::value_type scalar) const {
  Polynomial result = *this;
  result *= scalar;
  return result;
}

Polynomial Polynomial::operator / (const Polynomial& rhs) const {
  Polynomial result = *this;
  result /= rhs;
  return result;
}

Polynomial Polynomial::operator / (Polynomial::value_type scalar) const {
  Polynomial result = *this;
  result /= scalar;
  return result;
}

Polynomial Polynomial::operator % (const Polynomial& rhs) const {
  Polynomial result = *this;
  result %= rhs;
  return result;
}

Polynomial& Polynomial::operator += (const Monomial& rhs) {
  m_monomials.push_back(rhs);
  std::sort(m_monomials.begin(), m_monomials.end(), std::greater<Monomial>());
  squashSamePowers();
  return *this;
}

Polynomial& Polynomial::operator += (const Polynomial& rhs) {
  m_monomials.insert(m_monomials.end(), rhs.m_monomials.begin(), rhs.m_monomials.end());
  std::sort(m_monomials.begin(), m_monomials.end(), std::greater<Monomial>());
  squashSamePowers();
  return *this;
}

Polynomial& Polynomial::operator += (Polynomial::value_type scalar) {
  Monomial& last = m_monomials.back();
  if (last.m_power == 0) {
    last.m_coeff += scalar;
  } else {
    m_monomials.emplace_back(scalar);  // Monomial(scalar) ctor
  }
  return *this;
}

Polynomial& Polynomial::operator -= (const Monomial& rhs) {
  return *this += -rhs;
}

Polynomial& Polynomial::operator -= (const Polynomial& rhs) {
  return *this += -rhs;
}

Polynomial& Polynomial::operator -= (Polynomial::value_type scalar) {
  return *this += -scalar;
}

Polynomial& Polynomial::operator *= (const Monomial& rhs) {
  for (int i = 0; i < m_monomials.size(); ++i) {
    m_monomials[i] *= rhs;
  }
  m_power += rhs.getPower();
  return *this;
}

Polynomial& Polynomial::operator *= (const Polynomial& rhs) {
  Polynomial sum;
  for (auto& monomial : rhs.m_monomials) {
    sum += *this * monomial;
  }
  *this = sum;
  return *this;
}

Polynomial& Polynomial::operator *= (Polynomial::value_type scalar) {
  for (auto& monomial : m_monomials) {
    monomial *= scalar;
  }
  return *this;
}

Polynomial& Polynomial::operator /= (const Polynomial& rhs) {
  // TODO:
  return *this;
}

Polynomial& Polynomial::operator /= (Polynomial::value_type scalar) {
  for (auto& monomial : m_monomials) {
    monomial /= scalar;
  }
  return *this;
}

Polynomial& Polynomial::operator %= (const Polynomial& rhs) {
  // TODO:
  return *this;
}

bool Polynomial::operator == (const Polynomial& rhs) const {
  if (m_power != rhs.m_power) { return false; }
  // TODO:
}

bool Polynomial::operator != (const Polynomial& rhs) const {
  return !(*this == rhs);
}

Polynomial::value_type Polynomial::operator () (Polynomial::value_type value) const {
  Polynomial::value_type result = 0.0;
  for (auto& monomial : m_monomials) {
    result += monomial(value);  // Note: this is not a Horner's rule
  }
  return result;
}

Polynomial Polynomial::operator , (const Polynomial& rhs) const {
  // TODO:
}

/* end of Operators group */
// ------------------------------------------------------------------------------------------------

/* Maths group */
// ------------------------------------------------------------------------------------------------
// @see http://www.cplusplus.com/reference/functional/bind/
Polynomial Polynomial::derivative() const {
  Polynomial result;
  auto monomialDerivativeFunction = std::bind(&Monomial::derivative, std::placeholders::_1);
  std::transform(m_monomials.begin(), m_monomials.end(), result.m_monomials.begin(), monomialDerivativeFunction);
  return result;
}

/* end of Maths group */
// ------------------------------------------------------------------------------------------------
int Polynomial::calculatePower() const {
  int power = -9999999;
  for (auto& monomial : m_monomials) {
    if (power < monomial.getPower()) {
      power = monomial.getPower();
    }
  }
  return power;
}

void Polynomial::squashSamePowers() {
  std::vector<Monomial> monomials;
  monomials.reserve(m_monomials.size());

  Monomial aggregate = m_monomials.front();  // get reference to front item and copy into variable 'aggregate'
  for (int i = 1; i < m_monomials.size(); ++i) {
    Monomial prev = m_monomials[i - 1];
    Monomial current = m_monomials[i];
    if (prev.getPower() == current.getPower()) {
      aggregate += current;  // private Monomial::operator +=
    } else {
      monomials.push_back(aggregate);
      aggregate = current;
    }
  }
  monomials.push_back(aggregate);
  std::swap(m_monomials, monomials);
  m_power = calculatePower();
}

/* I/O */
// ------------------------------------------------------------------------------------------------
#include <cstdio>

std::ostream& operator << (std::ostream& out, const Polynomial& polynomial) {
  int index = -1;
  for (auto& monomial : polynomial.m_monomials) {
    ++index;
    if (index != 0 && monomial.getCoeff() < 0) {
      out << " - ";
      out << -monomial;
    } else if (util::equals(monomial.getCoeff(), 0.0)) {
      continue;  // skip zero monomials
    } else {
      if (index != 0) {
        out << " + ";
      }
      out << monomial;
    }
  }
  return out;
}

std::istream& operator >> (std::istream& in, Polynomial& polynomial) {
  std::string str;
  std::getline(in, str);
  std::istringstream iss(str);
  // TODO:
  return in;
}

void Polynomial::print() const {
  for (auto& monomial : m_monomials) {
    printf("%.3lfx^%i + ", monomial.getCoeff(), monomial.getPower());
  }
  printf("\n");
}

