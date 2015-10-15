#include "logger.h"

static void usage() {
  MSG("Usage: logging_sample_2 <parameter>");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Logging sample 2");

  if (argc < 2) {
    ERR("Invalid number of input parameters!");
    usage();
    return 1;
  } else {
    INF("Input parameter is: %s", argv[1]);
  }

  DBG("[Lesson 1]: Logging sample 2 [END]");
  return 0;
}

