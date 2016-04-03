#ifndef PROTOCOL_1__H__
#define PROTOCOL_1__H__

#include <ostream>
#include <string>
#include "protocol_0.h"

struct MCProtocol : public Protocol {
  int channel;

  MCProtocol();
  MCProtocol(const Protocol& rhs);

  bool operator == (const Protocol& rhs) const;
  bool operator == (const MCProtocol& rhs) const;
  bool operator != (const Protocol& rhs) const;
  bool operator != (const MCProtocol& rhs) const;
};

char* serialize_mc(const MCProtocol& message);
MCProtocol deserialize_mc(char* input);

std::ostream& operator << (std::ostream& out, const MCProtocol& message);

#endif  // PROTOCOL_1__H__

