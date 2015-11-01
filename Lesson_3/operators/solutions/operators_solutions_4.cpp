#include "polynomial.h"
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Operators: Solutions 4");

  std::default_random_engine rng;
  std::uniform_real_distribution<double> distribution(-10.0, 10.0);

  WRN("---------------------------------------------------------------------");
  WRN("-----------------  Operations with monomials  -----------------------");
  WRN("---------------------------------------------------------------------");
  {
    Monomial one(3, 2.71), two(2, 3.14), three(3, 5.15), four(1, -0.19), five(0, -6.87);
    std::cout << "\e[5;01;31mMonomial [one]:   \e[m" << one << "   \e[5;00;36mPower [" << one.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mMonomial [two]:   \e[m" << two << "   \e[5;00;36mPower [" << two.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mMonomial [three]:   \e[m" << three << "   \e[5;00;36mPower [" << three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mMonomial [four]:   \e[m" << four << "   \e[5;00;36mPower [" << four.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mMonomial [five]:   \e[m" << five << "   \e[5;00;36mPower [" << five.getPower() << "]\e[m" << std::endl;

    auto one_minus_two = one - two;
    auto two_plus_three = two + three;
    auto three_minus_three = three - three;
    auto four_plus_five = four + five;
    auto one_plus_two_minus_three_plus_four_minus_five = one + two - three + four - five;
    std::cout << "\e[5;00;32mUnary plus [one]: \e[m" << +one << std::endl;
    std::cout << "\e[5;00;32mUnary minus [two]: \e[m" << -two << std::endl;
    std::cout << "\e[5;00;32mOne - Two: \e[m" << one_minus_two << "   \e[5;00;36mPower [" << one_minus_two.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mTwo + Three: \e[m" << two_plus_three << "   \e[5;00;36mPower [" << two_plus_three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mThree - Three: \e[m" << three_minus_three << "   \e[5;00;36mPower [" << three_minus_three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mFour + Five: \e[m" << four_plus_five << "   \e[5;00;36mPower [" << four_plus_five.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mOne + Two - Three + Four - Five: \e[m" << one_plus_two_minus_three_plus_four_minus_five << "   \e[5;00;36mPower [" << one_plus_two_minus_three_plus_four_minus_five.getPower() << "]\e[m" << std::endl;

    auto one_multiply_three = one * three;
    auto two_divide_one = two / one;
    auto four_divide_five = four / five;
    auto three_multiply_two = three * two;
    auto one_multiply_five = one * five;
    auto two_multiply_four = two * four;
    auto one_divide_three = one / three;
    auto one_divide_two_plus_three_divide_two_minus_four_plus_five_multiply_three = one / two + three / two - four + five * three;
    std::cout << "\e[5;00;36mOne * Three: \e[m" << one_multiply_three << "   \e[5;00;36mPower [" << one_multiply_three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mTwo / One: \e[m" << two_divide_one << "   \e[5;00;36mPower [" << two_divide_one.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mFour / Five: \e[m" << four_divide_five << "   \e[5;00;36mPower [" << four_divide_five.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mThree * Two: \e[m" << three_multiply_two << "   \e[5;00;36mPower [" << three_multiply_two.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mOne * Five: \e[m" << one_multiply_five << "   \e[5;00;36mPower [" << one_multiply_five.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mTwo * Four: \e[m" << two_multiply_four << "   \e[5;00;36mPower [" << two_multiply_four.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mOne / Three: \e[m" << one_divide_three << "   \e[5;00;36mPower [" << one_divide_three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mOne / Two + Three / Two - Four + Five * Three: \e[m" << one_divide_two_plus_three_divide_two_minus_four_plus_five_multiply_three << "   \e[5;00;36mPower [" << one_divide_two_plus_three_divide_two_minus_four_plus_five_multiply_three.getPower() << "]\e[m" << std::endl;
  }

  WRN("---------------------------------------------------------------------");
  WRN("-----------------  Operations with polynomials  ---------------------");
  WRN("---------------------------------------------------------------------");
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
    std::cout << "\e[5;01;31mMonomial:   \e[m" << monomial << "   \e[5;00;36mPower [" << monomial.getPower() << "]\e[m" << std::endl;
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
    auto one_plus_two_minus_three_plus_single_minus_scalar = one + two - three + single - scalar;
    std::cout << "\e[5;00;32mOne + Two: \e[m" << one_plus_two << "   \e[5;00;36mPower [" << one_plus_two.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mTwo - Three: \e[m" << two_minus_three << "   \e[5;00;36mPower [" << two_minus_three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mThree - One: \e[m" << three_minus_one << "   \e[5;00;36mPower [" << three_minus_one.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mTwo - Two: \e[m" << two_minus_two << "   \e[5;00;36mPower [" << two_minus_two.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mOne + Two - Three + Single - Scalar: \e[m" << one_plus_two_minus_three_plus_single_minus_scalar << "   \e[5;00;36mPower [" << one_plus_two_minus_three_plus_single_minus_scalar.getPower() << "]\e[m" << std::endl;

    Polynomial four = util::create(&rng, distribution, 4);
    Polynomial five = util::create(&rng, distribution, 5);
    Polynomial six = util::create(&rng, distribution, 2);
    Polynomial seven = util::create(&rng, distribution, 3);
    Polynomial eight = util::create(&rng, distribution, 1);
    Polynomial nine = util::create(&rng, distribution, 9);
    Polynomial ten = util::create(&rng, distribution, 6);
    std::cout << "\e[5;01;31mPolynomial [Four]:   \e[m" << four << "   \e[5;00;36mPower [" << four.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Five]:   \e[m" << five << "   \e[5;00;36mPower [" << five.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Six]:    \e[m" << six << "   \e[5;00;36mPower [" << six.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Seven]:  \e[m" << seven << "   \e[5;00;36mPower [" << seven.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Eight]:  \e[m" << eight << "   \e[5;00;36mPower [" << eight.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Nine]:   \e[m" << nine << "   \e[5;00;36mPower [" << nine.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;01;31mPolynomial [Ten]:    \e[m" << ten << "   \e[5;00;36mPower [" << ten.getPower() << "]\e[m" << std::endl;

    auto two_mul_null = two * null;
    auto two_mul_zero = two * zero;
    auto two_mul_empty = two * empty;
    std::cout << "\e[5;00;36mTwo * Null: \e[m" << two_mul_null << "   \e[5;00;36mPower [" << two_mul_null.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mTwo * Zero: \e[m" << two_mul_zero << "   \e[5;00;36mPower [" << two_mul_zero.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;36mTwo * Empty: \e[m" << two_mul_empty << "   \e[5;00;36mPower [" << two_mul_empty.getPower() << "]\e[m" << std::endl;

    auto one_mul_single = one * single;
    auto one_mul_three = one * three;
    auto four_mul_five = four * five;
    auto six_mul_seven = six * seven;
    auto two_mul_monomial = two * monomial;
    auto eight_mul_ten_mul_five_minus_nine_mul_monomial = eight * ten * five - nine * monomial;
    std::cout << "\e[5;00;32mOne * Single: \e[m" << one_mul_single << "   \e[5;00;36mPower [" << one_mul_single.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mOne * Three: \e[m" << one_mul_three << "   \e[5;00;36mPower [" << one_mul_three.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mFour * Five: \e[m" << four_mul_five << "   \e[5;00;36mPower [" << four_mul_five.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mSix * Seven: \e[m" << six_mul_seven << "   \e[5;00;36mPower [" << six_mul_seven.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mTwo * Monomial: \e[m" << two_mul_monomial << "   \e[5;00;36mPower [" << two_mul_monomial.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mEight * Ten * Five - Nine * Monomial: \e[m" << eight_mul_ten_mul_five_minus_nine_mul_monomial << "   \e[5;00;36mPower [" << eight_mul_ten_mul_five_minus_nine_mul_monomial.getPower() << "]\e[m" << std::endl;

    auto five_div_seven = five / seven;
    auto five_mod_seven = five % seven;
    auto five_check = seven * five / seven + five_mod_seven;
    std::cout << "\e[5;00;32mFive / Seven: \e[m" << five_div_seven << "   \e[5;00;36mPower [" << five_div_seven.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mFive mod Seven: \e[m" << five_mod_seven << "   \e[5;00;36mPower [" << five_mod_seven.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;33mFive / Seven [Check]: \e[m" << five_check << "   \e[5;00;36mPower [" << five_check.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;33mEquality: (Five) and (Seven * Five / Seven + Five mod Seven): \e[m" << std::boolalpha << (five_check == five) << std::endl;

    //auto four_minus_five_plus_six_mul_seven_minus_eight_plus_nine_div_ten = four - five + six * seven - eight + nine / ten;
    auto five_minus_five = five - five;
    auto four_plus_four = four + four;
    auto four_mul_2 = four * 2.0;
    //auto five_mul_six_mul_seven_div_ten_plus_four_mul_six_div_seven_minus_four_div_eight_mul_nine = five * six * seven / ten + four * six / seven - four / eight * nine;
    //std::cout << "\e[5;00;32mFour - Five + Six * Seven - Eight + Nine / Ten: \e[m" << four_minus_five_plus_six_mul_seven_minus_eight_plus_nine_div_ten << "   \e[5;00;36mPower [" <<  four_minus_five_plus_six_mul_seven_minus_eight_plus_nine_div_ten.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mFive - Five: \e[m" << five_minus_five << "   \e[5;00;36mPower [" << five_minus_five.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mFour + Four: \e[m" << four_plus_four << "   \e[5;00;36mPower [" << four_plus_four.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;32mFour * 2: \e[m" << four_mul_2 << "   \e[5;00;36mPower [" << four_mul_2.getPower() << "]\e[m" << std::endl;
    std::cout << "\e[5;00;33mEquality: (Four + Four) and (Four * 2): \e[m" << std::boolalpha << (four_plus_four == four_mul_2) << std::endl;
    //std::cout << "\e[5;00;32mFive * Six * Seven / Ten + Four * Six / Seven - Four / Eight * Nine: \e[m" << five_mul_six_mul_seven_div_ten_plus_four_mul_six_div_seven_minus_four_div_eight_mul_nine << "   \e[5;00;36mPower [" << five_mul_six_mul_seven_div_ten_plus_four_mul_six_div_seven_minus_four_div_eight_mul_nine.getPower() << "]\e[m" << std::endl;
  }

  WRN("---------------------------------------------------------------------");
  WRN("-----------------  Input polynomial from stdin  ---------------------");
  WRN("---------------------------------------------------------------------");
  {
    Monomial monomial;
    // std::cin >> monomial;
    std::cout << "Monomial: " << monomial << std::endl;
  }

  DBG("[Lesson 3]: Operators: Solutions 4 [END]");
  return 0;
}

