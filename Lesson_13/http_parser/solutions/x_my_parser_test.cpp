#include <iostream>
#include <cstdio>
#include "logger.h"
#include "solutions/x_my_parser.h"

int main(int argc, char** argv) {

  char* response = "HTTP/1.1 202 Accepted\r\n\
    Vary: Authorization,Accept\r\n\
    Transfer-Encoding: chunked\r\n\
    Location: https://api.bonfire-project.eu:444/experiments/336\r\n\
    Content-Type: text/html; charset=utf-8\r\n\
    Date: Wed, 01 Jun 2011 15:00:05 GMT\r\n\
    Server: thin 1.2.11 codename Bat-Shit Crazy\r\n\
    Cache-Control: no-cache\r\n\
    Connection: close\r\n\r\n";

  char* body_response = "HTTP/1.1 200 OK\r\n\
    Vary: Authorization,Accept\r\n\
    Transfer-Encoding: chunked\r\n\
    Etag: \"fa2ba873343ba638123b7671c8c09998\"\r\n\
    Content-Type: application/vnd.bonfire+xml; charset=utf-8\r\n\
    Date: Wed, 01 Jun 2011 14:59:30 GMT\r\n\
    Server: thin 1.2.11 codename Bat-Shit Crazy\r\n\
    Allow: GET,OPTIONS,HEAD\r\n\
    Cache-Control: public,max-age=120\r\n\
    Connection: close\r\n\
    \r\n\
    <?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
    <root xmlns=\"http://api.bonfire-project.eu/doc/schemas/occi\" href=\"/\">\r\n\
      <version>0.8.9</version>\r\n\
      <timestamp>1306940370</timestamp>\r\n\
      <link rel=\"experiments\" href=\"/experiments\" type=\"application/vnd.bonfire+xml\"/>\r\n\
      <link rel=\"locations\" href=\"/locations\" type=\"application/vnd.bonfire+xml\"/>\r\n\
      <link rel=\"users\" href=\"/users\" type=\"application/vnd.bonfire+xml\"/>\r\n\
    </root>\r\n";

  XMyParser parser;

  Response parsed = parser.parseResponse(response, 0);
  printf("\n----------------------------------------------\n");
  Response parsed_body = parser.parseResponse(body_response, 0);

  std::cout << parsed << std::endl;
  std::cout << parsed_body << std::endl;

  return 0;
}

