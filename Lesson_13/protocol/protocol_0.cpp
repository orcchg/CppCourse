#include <cstring>
#include "logger.h"
#include "protocol_0.h"

bool Protocol::operator == (const Protocol& rhs) const {
  return ((src_id == rhs.src_id) &&
         (dest_id == rhs.dest_id) &&
         (timestamp == rhs.timestamp) &&
         (name == rhs.name) &&
         (message == rhs.message));
}

bool Protocol::operator != (const Protocol& rhs) const {
  return !(*this == rhs);
}

/* Serialization */
// ----------------------------------------------------------------------------
void serialize(const Protocol& message, char* output) {
  output = new char[6 + 3 * sizeof(int) + message.name.length() + message.message.length()];

  std::string src_id_src = std::to_string(message.src_id);
  std::string dest_id_src = std::to_string(message.dest_id);
  std::string ts_src = std::to_string(message.timestamp);

  strncpy(output, src_id_src.c_str(), src_id_src.length());
  output += src_id_src.length();
  strncpy(output, "#", 1);
  output += 1;

  strncpy(output, dest_id_src.c_str(), dest_id_src.length());
  output += dest_id_src.length();
  strncpy(output, "#", 1);
  output += 1;

  strncpy(output, ts_src.c_str(), ts_src.length());
  output += ts_src.length();
  strncpy(output, "#", 1);
  output += 1;

  strncpy(output, message.name.c_str(), message.name.length());
  output += message.name.length();
  strncpy(output, "#", 1);
  output += 1;

  strncpy(output, message.message.c_str(), message.message.length());
  output += message.message.length();
  strncpy(output, "#", 1);
  output += 1;
  strncpy(output, "\0", 1);

  MSG("Serialized: %s", output);
}

Protocol deserialize(char* input) {
  if (input == nullptr) {
    ERR("Null input, nothing to deserialize");
    throw SerializeException();
  }

  MSG("Deserialize: %s", input);

  std::string wrap(input);
  int i1 = wrap.find_first_of('#');
  std::string src_id_str = wrap.substr(0, i1);
  int i2 = wrap.find_first_of('#', i1 + 1);
  std::string dest_id_str = wrap.substr(i1 + 1, i2);
  int i3 = wrap.find_first_of('#', i2 + 1);
  std::string ts_str = wrap.substr(i2 + 1, i3);
  int i4 = wrap.find_first_of('#', i3 + 1);
  std::string name = wrap.substr(i3 + 1, i4);
  std::string message = wrap.substr(i4 + 1);

  Protocol protocol;
  protocol.src_id = std::atoi(src_id_str.c_str());
  protocol.dest_id = std::atoi(dest_id_str.c_str());
  protocol.timestamp = std::atoi(ts_str.c_str());
  protocol.name = name;
  protocol.message = message;

  return protocol;
}

std::ostream& operator << (std::ostream& out, const Protocol& message) {
  out << "{\nsrc_id = " << message.src_id
      << "\t\ndest_id = " << message.dest_id
      << "\t\nt = " << message.timestamp
      << "\t\nname = " << message.name
      << "\t\nmessage = " << message.message
      << "\n}";
  return out;
}

