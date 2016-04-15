#ifndef MY_PARSER__H__
#define MY_PARSER__H__

#include <string>
#include <vector>

struct Header {
  std::string name;
  std::string value;
};

struct Request {
  std::string method;
  std::string path;
  int version;
  std::vector<Header> headers;
  std::string body;
};

class MyParser {
public:
  MyParser();
  virtual ~MyParser();

  Request parseRequest(char* http, int nbytes);

private:
  bool isHeader(const std::string& header_line) const;
};

#endif  // MY_PARSER__H__

