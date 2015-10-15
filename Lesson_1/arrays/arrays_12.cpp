#include <vector>
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 12");

  std::vector<double> array = {5.14, 10.11, 15.57, 11.83, 9.99, 4.33, -6.27, 8.87, 1.7, 22.1, 3.68, -2.01, 1., 0.19};
  for (double item : array) {
    printf("%.2lf ", item);
  }
  printf("\n");

  DBG("[Lesson 1]: Arrays 12 [END]");
  return 0;
}

