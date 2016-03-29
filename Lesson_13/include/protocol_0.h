#ifndef PROTOCOL_0__H__
#define PROTOCOL_0__H__

#include <ostream>
#include <string>

struct Protocol {
  int src_id;
  int dest_id;
  long long timestamp;
  std::string name;
  std::string message;

  bool operator == (const Protocol& rhs) const;
  bool operator != (const Protocol& rhs) const;
};

static Protocol EMPTY_MESSAGE;

struct SerializeException {};

char* serialize(const Protocol& message);
Protocol deserialize(char* input);

std::ostream& operator << (std::ostream& out, const Protocol& message);

#endif  // PROTOCOL_0__H__

