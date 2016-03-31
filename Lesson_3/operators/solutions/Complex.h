#include <algorithm>
#include "logger.h"

/* Complex number */
// ----------------------------------------------------------------------------
class Complex {
public:
  Complex();
  Complex(double real, double image);
  Complex(const Complex& obj);
  ~Complex();

  Complex& operator = (Complex rhs);

  double getReal() const { return m_real; }
  double getImage() const { return m_image; }

  /**
   * @defgroup Operators Overloading of common operations
   * @{
   */
  // binary
  Complex operator + (const Complex& rhs) const;
  Complex operator - (const Complex& rhs) const;
  Complex operator * (const Complex& rhs) const;
  Complex operator / (const Complex& rhs) const;

  Complex& operator += (const Complex& rhs);
  Complex& operator -= (const Complex& rhs);
  Complex& operator *= (const Complex& rhs);
  Complex& operator /= (const Complex& rhs);

  bool operator == (const Complex& rhs) const;
  bool operator != (const Complex& rhs) const;

  // unary
  Complex operator + () const;
  Complex operator - () const;
  Complex& operator ++ ();
  Complex operator ++ (int);
  Complex& operator -- ();
  Complex operator -- (int);
  /** @} */  // end of Operators group

private:
  double m_real;
  double m_image;
};

/* Initialization */
// ----------------------------------------------
Complex::Complex()
  : m_real(0.0)
  , m_image(0.0) {
  //INF("Default Constructor");
}

Complex::Complex(double real, double image)
  : m_real(real)
  , m_image(image) {
  //INF("Constructor(double, double)");
}

Complex::Complex(const Complex& obj)
  : m_real(obj.m_real)
  , m_image(obj.m_image) {
  //CRT("Copy Constructor");
}

Complex::~Complex() {
  //INF("~Destructor");
}

Complex& Complex::operator = (Complex rhs) {
  //WRN("Assigment Operator");
  std::swap(m_real, rhs.m_real);
  std::swap(m_image, rhs.m_image);
  return *this;
}

/* Group Operators */
// ----------------------------------------------
// binary
Complex Complex::operator + (const Complex& rhs) const {
  Complex temporary(*this);
  return temporary += rhs;
}

Complex Complex::operator - (const Complex& rhs) const {
  Complex temporary(*this);
  return temporary -= rhs;
}

Complex Complex::operator * (const Complex& rhs) const {
  Complex temporary(*this);
  return temporary *= rhs;
}

Complex Complex::operator / (const Complex& rhs) const {
  Complex temporary(*this);
  return temporary /= rhs;
}

Complex& Complex::operator += (const Complex& rhs) {
  m_real += rhs.m_real;
  m_image += rhs.m_image;
  return *this;
}

Complex& Complex::operator -= (const Complex& rhs) {
  m_real -= rhs.m_real;
  m_image -= rhs.m_image;
  return *this;
}

Complex& Complex::operator *= (const Complex& rhs) {
  double real = m_real * rhs.m_real - m_image * rhs.m_image;
  double image = m_image * rhs.m_real + m_real * rhs.m_image;
  m_real = real;
  m_image = image;
  return *this;
}

Complex& Complex::operator /= (const Complex& rhs) {
  double denominator = rhs.m_real * rhs.m_real + rhs.m_image * rhs.m_image;
  double real = (m_real * rhs.m_real + m_image * rhs.m_image) / denominator;
  double image = (m_image * rhs.m_real - m_real * rhs.m_image) / denominator;
  m_real = real;
  m_image = image;
  return *this;
}

bool Complex::operator == (const Complex& rhs) const {
  return m_real == rhs.m_real && m_image == rhs.m_image;
}

bool Complex::operator != (const Complex& rhs) const {
  return !(*this == rhs);
}

// unary
Complex Complex::operator + () const {
  return Complex(*this);
}

Complex Complex::operator - () const {  // Quiz: is this Conjugation?
  Complex temporary(*this);
  temporary.m_real *= -1;
  temporary.m_image *= -1;
  return temporary;
}

Complex& Complex::operator ++ () {
  ++m_real;
  ++m_image;
  return *this;
}

Complex Complex::operator ++ (int) {
  Complex old = *this;
  ++(*this);
  return old;
}

Complex& Complex::operator -- () {
  --m_real;
  --m_image;
  return *this;
}

Complex Complex::operator -- (int) {
  Complex old = *this;
  --(*this);
  return old;
}

