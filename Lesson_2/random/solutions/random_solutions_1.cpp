#include <iostream>
#include <random>
#include "logger.h"

int main() {
  DBG("[Lesson 2]: Random: Solutions 1");

  const int nrolls = 10000;  // number of experiments
  const int nstars = 100;    // maximum number of stars to distribute

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(5.0, 2.0);

  int p[10] = {};

  for (int i = 0; i < nrolls; ++i) {
    double number = distribution(generator);
    if ((number >= 0.0) && (number < 10.0)) ++p[int(number)];
  }

  for (int i = 0; i < 10; ++i) {
    std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
  }

  DBG("[Lesson 2]: Random: Solutions 1 [END]");
  return 0;
}

