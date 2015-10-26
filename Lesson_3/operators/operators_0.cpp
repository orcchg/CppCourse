#include <algorithm>
#include <iostream>
#include <cstdio>
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

private:
  double m_real;
  double m_image;
};

/* Initialization */
// ----------------------------------------------
Complex::Complex()
  : m_real(0.0)
  , m_image(0.0) {
}

Complex::Complex(double real, double image)
  : m_real(real)
  , m_image(image) {
}

Complex::Complex(const Complex& obj)
  : m_real(obj.m_real)
  , m_image(obj.m_image) {
}

Complex::~Complex() {
}

Complex& Complex::operator = (Complex rhs) {
  std::swap(m_real, rhs.m_real);
  std::swap(m_image, rhs.m_image);
  return *this;
}

/* Input / Output */
// ----------------------------------------------
std::ostream& operator << (std::ostream& out, const Complex& obj) {
  out << "(" << obj.getReal() << ", " << obj.getImage() << "i)";
  return out;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 3]: Operators 0");

  double real, image;
  printf("\e[5;00;32mВведите комплексное число: \e[m");
  scanf("%lf %lf", &real, &image);

  Complex complex(real, image);
  std::cout << "Комплексное число: " << complex << std::endl;

  DBG("[Lesson 3]: Operators 0 [END]");
  return 0;
}

