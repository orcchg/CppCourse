#ifndef X_MY_PARSER__H__
#define X_MY_PARSER__H__

#include "my_parser.h"

struct CodeLine {
  int version;
  int code;
  std::string message;
};

struct Response {
  CodeLine codeline;
  std::vector<Header> headers;
  std::string body;
};

std::ostream& operator << (std::ostream& out, const CodeLine& codeline);
std::ostream& operator << (std::ostream& out, const Response& response);

class XMyParser : public MyParser {
public:
  XMyParser();
  virtual ~XMyParser();

  Response parseResponse(char* http, int nbytes);

protected:
  CodeLine parseCodeLine(const std::string& code_line) const;
};

#endif  // X_MY_PARSER__H__

