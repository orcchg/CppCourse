#ifndef PROTOCOL_0__H__
#define PROTOCOL_0__H__

#include <ostream>
#include <string>

struct Protocol {
  int src_id;
  int dest_id;
  int timestamp;
  std::string name;
  std::string message;

  bool operator == (const Protocol& rhs) const;
  bool operator != (const Protocol& rhs) const;
};

struct SerializeException {};

void serialize(const Protocol& message, char* output);
Protocol deserialize(char* input);

std::ostream& operator << (std::ostream& out, const Protocol& message);

#endif  // PROTOCOL_0__H__

