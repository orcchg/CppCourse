#include <complex>
#include <random>
#include <cmath>
#include <ctime>
#include "Complex.h"

bool equal(double lhs, double rhs) {
  return std::abs(lhs - rhs) < 0.00001;
}

bool compare(const std::complex<double>& expected, const Complex& actual) {
  return equal(actual.getReal(), expected.real()) && equal(actual.getImage(), expected.imag());
}

void print(const std::complex<double>& expected, const Complex& actual) {
  DBG("expected = (%.2lf, %.2lfi), actual = (%.2lf, %.2lfi)",
    expected.real(), expected.imag(), actual.getReal(), actual.getImage());
}

void unitTest() {
  clock_t start = clock();
  clock_t elapsed = start;
  bool flag = true;
  size_t total_tests = 0;

  std::default_random_engine rng;
  std::normal_distribution<double> distribution(0.0, 20.0);

  while (flag && (elapsed - start) < 1 * CLOCKS_PER_SEC) {
    ++total_tests;
    double real_one = distribution(rng);
    double image_one = distribution(rng);
    double real_two = distribution(rng);
    double image_two = distribution(rng);

    Complex actual_one(real_one, image_one);
    Complex actual_two(real_two, image_two);
    std::complex<double> expected_one(real_one, image_one);
    std::complex<double> expected_two(real_two, image_two);

    Complex actual_add = actual_one + actual_two;
    std::complex<double> expected_add = expected_one + expected_two;
    if (!compare(expected_add, actual_add)) {
      flag = false;
      ERR("Addition error");
      print(expected_add, actual_add);
      DBG("Test case");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
    }

    Complex actual_sub = actual_one - actual_two;
    std::complex<double> expected_sub = expected_one - expected_two;
    if (!compare(expected_sub, actual_sub)) {
      flag = false;
      ERR("Subtraction error");
      print(expected_sub, actual_sub);
      DBG("Test case");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
    }

    Complex actual_mul = actual_one * actual_two;
    std::complex<double> expected_mul = expected_one * expected_two;
    if (!compare(expected_mul, actual_mul)) {
      flag = false;
      ERR("Multiplication error");
      print(expected_mul, actual_mul);
      DBG("Test case");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
    }

    Complex actual_div = actual_one / actual_two;
    std::complex<double> expected_div = expected_one / expected_two;
    if (!compare(expected_div, actual_div)) {
      flag = false;
      ERR("Division error");
      print(expected_div, actual_div);
      DBG("Test case");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
    }

    bool actual_equal = actual_one == actual_two;
    bool expected_equal = expected_one == expected_two;
    if (actual_equal != expected_equal) {
      flag = false;
      ERR("Equality error");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
      DBG("Test case");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
    }

    bool actual_not_equal = actual_one != actual_two;
    bool expected_not_equal = expected_one != expected_two;
    if (actual_not_equal != expected_not_equal) {
      flag = false;
      ERR("Inequality error");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
      DBG("Test case");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
    }

    if (flag) {
      INF("OK");
      print(expected_one, actual_one);
      print(expected_two, actual_two);
    }

    elapsed = clock();
  }
  WRN("Total tests: %zu", total_tests);
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Operators: Solutions 2");
  unitTest();
  DBG("[Lesson 3]: Operators: Solutions 2 [END]");
  return 0;
}

