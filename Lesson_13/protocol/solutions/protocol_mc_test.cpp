#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>
#include "logger.h"
#include "solutions/protocol_1.h"

int main(int argc, char** argv) {
  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  MCProtocol protocol;
  protocol.src_id = 789;
  protocol.dest_id = 1234;
  protocol.timestamp = millis;
  protocol.name = "Maxim";
  protocol.message = "Hello, World!";
  protocol.channel = 500;

  std::ostringstream oss;
  oss << protocol;
  DBG("Init: %s", oss.str().c_str());

  char* buffer = serialize_mc(protocol);

  Protocol output = deserialize_mc(buffer);

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

