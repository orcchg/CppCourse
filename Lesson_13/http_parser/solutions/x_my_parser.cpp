#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include "logger.h"
#include "solutions/x_my_parser.h"

XMyParser::XMyParser() {
}

XMyParser::~XMyParser() {
}

Response XMyParser::parseResponse(char* http, int nbytes) {
  const char* CRLF = "\r\n";
  std::istringstream iss(http);
  //MSG("Input: %s", iss.str().c_str());
  Response response;

  // code line
  std::string code_line;
  std::getline(iss, code_line);
  //MSG("code=%s", code_line.c_str());
  response.codeline = parseCodeLine(code_line);

  // headers
  std::string header_line;
  std::vector<Header> headers;
  while (true) {
    std::getline(iss, header_line);
    if (isHeader(header_line)) {
      Header header = parseHeader(header_line);
      headers.push_back(header);
      //MSG("header=%s", header_line.c_str());
    } else {
      break;
    }
  }
  response.headers = headers;

  // body
  std::string ending = "";
  response.body = "";
  std::string line;
  while (std::getline(iss, line)) {
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    response.body.append(ending);
    response.body.append(line);
    ending = "\n";
  }

  return response;
}

/* Output */
// ----------------------------------------------------------------------------
std::ostream& operator << (std::ostream& out, const CodeLine& codeline) {
  out << "Code Line:\n\tVersion: " << codeline.version << "\n\tCode: " << codeline.code << "\n\tMessage: " << codeline.message << std::endl;
  return out;
}

std::ostream& operator << (std::ostream& out, const Response& response) {
  out << "Response:\n" << response.codeline;
  for (auto& it : response.headers) {
    out << it;
  }
  out << "Body:\n" << response.body << std::endl;
  return out;
}

/* Internals */
// ----------------------------------------------------------------------------
CodeLine XMyParser::parseCodeLine(const std::string& code_line) const {
  reduce(code_line);
  CodeLine codeline;
  int i1 = code_line.find_first_of("HTTP");
  codeline.version = std::atoi(code_line.substr(i1 + 7, 1).c_str());
  int i2 = code_line.find_first_of(" ", i1 + 8);
  int i3 = code_line.find_first_of(" ", i2 + 1);
  codeline.code = std::atoi(code_line.substr(i2, i3 - i2).c_str());
  codeline.message = code_line.substr(i3 + 1);
  return codeline;
}

