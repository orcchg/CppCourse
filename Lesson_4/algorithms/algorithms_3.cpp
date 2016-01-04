#include <algorithm>
#include <iostream>
#include <iterator>  // back_inserter
#include <functional>  // multiplies
#include <numeric>  // accumulate
#include <vector>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 3");

  std::vector<double> first = {3.14, 2.71, 5.19, 0.01, -4.7};
  std::vector<double> second = {9.7, 2.5, -11.2, -7.9, 0.2};
  std::vector<double> factors;

  std::transform(first.begin(), first.end(), second.begin(), std::back_inserter(factors), std::multiplies<double>());
  std::copy(factors.begin(), factors.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;

  double scalar_product = std::accumulate(factors.begin(), factors.end(), 0.0, std::plus<double>());
  INF("Scalar product: %lf", scalar_product);

  DBG("[Lesson 4]: Algorithms 3 [END]");
  return 0;
}

