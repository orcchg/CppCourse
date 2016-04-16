#include <algorithm>
#include <ctime>
#include <sstream>
#include "logger.h"
#include "solutions/convert_json.h"
#include "solutions/protocol_1.h"

int main(int argc, char** argv) {
  MCProtocol protocol;
  protocol.src_id = 789;
  protocol.dest_id = 1234;
  protocol.timestamp = 1460770067734;
  protocol.channel = 500;
  protocol.name = "Maxim";
  protocol.message = "Hello, World!";

  std::ostringstream oss;
  oss << protocol;
  DBG("Init: %s", oss.str().c_str());

  std::string json = "{\"src_id\":789,\"dest_id\":1234,\"channel\":500,\"timestamp\":1460770067734,\"name\":\"Maxim\",\"message\":\"Hello, World!\"}";
  DBG("Init JSON: %s", json.c_str());

  DBG("Test: from JSON");
  MCProtocol protocol_from_json = fromJson(json);
  if (protocol == protocol_from_json) {
    INF("OK");
  } else {
    ERR("Failed test from JSON!");
    oss.str("");
    oss << protocol_from_json;
    MSG("Actual: %s", oss.str().c_str());
  }

  DBG("Test: to JSON");
  std::string json_from_protocol = toJson(protocol);
  if (json == json_from_protocol) {
    INF("OK");
  } else {
    ERR("Failed test to JSON!");
    MSG("Actual: %s", json_from_protocol.c_str());
  }

  return 0;
}

