#include <algorithm>  // for std::max_element, std::transform
#include <iostream>
#include <random>
#include "logger.h"

const int nrolls = 10000;  // number of experiments
const int nstars = 100;    // maximum number of stars to distribute

int trim(int value) {
  return value * nstars / nrolls;
}

void output(int p[]) {
  std::transform(p, p + 10, p, trim);
  int height = *std::max_element(p, p + 10);

  for (int h = height; h > 0; --h) {
    for (int i = 0; i < 10; ++i) {
      if (p[i] < h) {
        std::cout << "  ";
      } else {
        std::cout << "* ";
      }
    }
    std::cout << "\n";
  }
}

int main() {
  DBG("[Lesson 2]: Random: Solutions 2");

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(5.0, 2.0);

  int p[10] = {};

  for (int i = 0; i < nrolls; ++i) {
    double number = distribution(generator);
    if ((number >= 0.0) && (number < 10.0)) ++p[int(number)];
  }

  output(p);

  DBG("[Lesson 2]: Random: Solutions 2 [END]");
  return 0;
}

