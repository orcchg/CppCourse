#include "polynomial.h"
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Operators: Solutions 4");

  std::default_random_engine rng;
  std::uniform_real_distribution<double> distribution(-10.0, 10.0);

  WRN("---------------------------------------------------------------------");
  INF("Operations with polynomials");
  {
    std::vector<Monomial> zeroes(2);  // 2 default Monomial instances

    Monomial monomial(3, 2.71);
    Polynomial null;
    Polynomial zero(zeroes);
    Polynomial empty = util::create(&rng, distribution, 0);
    Polynomial scalar = util::create(&rng, distribution, 1);
    Polynomial single = util::create(&rng, distribution, 2);
    Polynomial one = util::create(&rng, distribution, 5);
    Polynomial two = util::create(&rng, distribution, 8);
    Polynomial three = util::create(&rng, distribution, 3);
    std::cout << "\e[5;01;31mMonomial :   \e[m" << monomial << "   \e[5;00;36mPower [" << monomial.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Null]:     \e[m" << null << "   \e[5;00;36mPower [" << null.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Zero]:     \e[m" << zero << "   \e[5;00;36mPower [" << zero.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Empty]:    \e[m" << empty << "   \e[5;00;36mPower [" << empty.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Scalar]:   \e[m" << scalar << "   \e[5;00;36mPower [" << scalar.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Single]:   \e[m" << single << "   \e[5;00;36mPower [" << single.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [One]:      \e[m" << one << "   \e[5;00;36mPower [" << one.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Two]:      \e[m" << two << "   \e[5;00;36mPower [" << two.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Three]:    \e[m" << three << "   \e[5;00;36mPower [" << three.getPower() << "]\e[m" << std::endl;

    auto plus_one = +one;
    auto minus_one = -one;
    auto one_plus_monomial = one + monomial;
    auto two_minus_monomial = two - monomial;
    auto three_plus_monomial = three + monomial;
    std::cout << "\e[5;00;36mUnary plus: \e[m" << plus_one << "   \e[5;00;36mPower [" << plus_one.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mUnary minus: \e[m" << minus_one << "   \e[5;00;36mPower [" << minus_one.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mOne + Monomial: \e[m" << one_plus_monomial << "   \e[5;00;36mPower [" << one_plus_monomial.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mTwo - Monomial: \e[m" << two_minus_monomial << "   \e[5;00;36mPower [" << two_minus_monomial.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mThree + Monomial: \e[m" << three_plus_monomial << "   \e[5;00;36mPower [" << three_plus_monomial.getPower() << "]\e[m" << std::endl;

    auto one_plus_two = one + two;
    auto two_minus_three = two - three;
    auto three_minus_one = three - one;
    auto two_minus_two = two - two;
    std::cout << "\e[5;00;32mOne + Two: \e[m" << one_plus_two << "   \e[5;00;36mPower [" << one_plus_two.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mTwo - Three: \e[m" << two_minus_three << "   \e[5;00;36mPower [" << two_minus_three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mThree - One: \e[m" << three_minus_one << "   \e[5;00;36mPower [" << three_minus_one.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mTwo - Two: \e[m" << two_minus_two << "   \e[5;00;36mPower [" << two_minus_two.getPower() << "]\e[m" << std::endl;
  }

  WRN("---------------------------------------------------------------------");
  INF("Input polynomial from stdin");
  {
    Monomial monomial;
    //std::cin >> monomial;
    std::cout << "Monomial: " << monomial << std::endl;
  }

  DBG("[Lesson 3]: Operators: Solutions 4 [END]");
  return 0;
}

