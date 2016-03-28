#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>
#include "logger.h"
#include "protocol_0.h"

int main(int argc, char** argv) {
  std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(point);
  std::ostringstream oss;
  oss << std::ctime(&time);

  Protocol protocol;
  protocol.src_id = 789;
  protocol.dest_id = 1234;
  protocol.timestamp = std::atoi(oss.str().c_str());
  protocol.name = "Maxim";
  protocol.message = "Hello, World!";

  oss.str("");
  oss << protocol;
  DBG("Init: %s", oss.str().c_str());

  char* buffer = nullptr;
  serialize(protocol, buffer);

  Protocol output = deserialize(buffer);
  if (output == protocol) {
    INF("Test passed: OK");
  } else {
    ERR("Test failed!");
    oss.str("");
    oss << protocol;
    ERR("Expected: %s", oss.str().c_str());
    oss.str("");
    oss << output;
    ERR("Actual: %s", oss.str().c_str());
  }

  delete [] buffer;

  return 0;
}

