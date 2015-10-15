#include <cstdio>
#include "logger.h"

static void usage() {
  MSG("Usage: logging_sample_3 <parameter>");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Logging sample 3");

  int numerator = 0, denominator = 1;
  INF("Enter numerator and denominator: ");
  scanf("%i %i", &numerator, &denominator);

  if (denominator == 0) {
    WRN("Denominator is zero!");
    return 1;
  }

  INF("Quotient is: %lf", static_cast<double>(numerator) / denominator);

  DBG("[Lesson 1]: Logging sample 3 [END]");
  return 0;
}

