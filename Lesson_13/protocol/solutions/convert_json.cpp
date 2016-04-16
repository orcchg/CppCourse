#include <sstream>
#include "logger.h"
#include "solutions/convert_json.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

/**
 *  Initial structure:
 *
 *  struct MCProtocol {
 *    int src_id;
 *    int dest_id;
 *    int channel;
 *    long long timestamp;
 *    std::string name;
 *    std::string message;
 *  };
 */
// ----------------------------------------------
/**
 *  JSON:
 *
 *  {
 *    "src_id": 1000,
 *    "dest_id": 2000,
 *    "channel": 5,
 *    "timestamp": 1460770067734,
 *    "name": "Artem",
 *    "message": "Hello, I'm Artem"
 *  }
 */
// ----------------------------------------------

std::string toJson(const MCProtocol& protocol) {
  std::ostringstream oss;
  oss << "{\"src_id\":" << protocol.src_id
      << ",\"dest_id\":" << protocol.dest_id
      << ",\"channel\":" << protocol.channel
      << ",\"timestamp\":" << protocol.timestamp
      << ",\"name\":\"" << protocol.name
      << "\",\"message\":\"" << protocol.message
      << "\"}";
  return oss.str();
}

MCProtocol fromJson(const std::string& json) {
  const char* ITEM_SRC_ID = "src_id";
  const char* ITEM_DEST_ID = "dest_id";
  const char* ITEM_CHANNEL = "channel";
  const char* ITEM_TIMESTAMP = "timestamp";
  const char* ITEM_NAME = "name";
  const char* ITEM_MESSAGE = "message";

  MCProtocol protocol;
  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.IsObject()) {
    protocol.src_id = document[ITEM_SRC_ID].GetInt();
    protocol.dest_id = document[ITEM_DEST_ID].GetInt();
    protocol.channel = document[ITEM_CHANNEL].GetInt();
    protocol.timestamp = document[ITEM_TIMESTAMP].GetInt64();
    protocol.name = document[ITEM_NAME].GetString();
    protocol.message = document[ITEM_MESSAGE].GetString();
  }
  return protocol;
}

