#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Logging sample 1");

  if (argc < 2) {
    ERR("Invalid number of input parameters!");
    return 1;
  } else {
    INF("Input parameter is: %s", argv[1]);
  }

  DBG("[Lesson 1]: Logging sample 1 [END]");
  return 0;
}

