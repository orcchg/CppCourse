#include <sstream>
#include "logger.h"
#include "my_parser.h"

MyParser::MyParser() {
}

MyParser::~MyParser() {
}

Request MyParser::parseRequest(char* http, int nbytes) {
  const char* CRLF = "\r\n";
  std::istringstream iss(http);

  // start line
  std::string start_line;
  std::getline(iss, start_line);
  MSG("start=%s", start_line.c_str());

  // headers
  std::string header_line;
  do {
    std::getline(iss, header_line);
    MSG("header=%s", header_line.c_str());
  } while (isHeader(header_line));

  // body
  int body_index = iss.tellg();
  MSG("body index=%i", body_index);
  iss.seekg(0, iss.end);
  int body_length = iss.tellg();
  body_length -= body_index;
  
  if (body_length > 0) {
    iss.seekg(body_index);
    MSG("length=%i", body_length);
    char* buffer = new char[body_length];
    iss.read(buffer, body_length);
    std::string body(buffer);
    delete [] buffer;
    MSG("body=%s", body.c_str());
  } else {
    MSG("No body");
  }

  // compose request
  Request request;
  return request;  
}

bool MyParser::isHeader(const std::string& header_line) const {
  int colon = header_line.find_first_of(':');
  return colon != std::string::npos;
}

