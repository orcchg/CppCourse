#ifndef CONVERT_JSON__H__
#define CONVERT_JSON__H__

#include <string>
#include "solutions/protocol_1.h"

std::string toJson(const MCProtocol& protocol);
MCProtocol fromJson(const std::string& json);

#endif  // CONVERT_JSON__H__

