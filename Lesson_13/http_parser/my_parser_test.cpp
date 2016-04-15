#include <iostream>
#include <cstdio>
#include "logger.h"
#include "my_parser.h"

int main(int argc, char** argv) {

  char* request = "GET / HTTP/1.1\r\n\
    Host: api.bonfire-project.eu:444\r\n\
    Accept: */*\r\n\
    Authorization: Basic XXX\r\n\
    Accept-Encoding: gzip, deflate\r\n\r\n";

  char* body_request = "POST /experiments HTTP/1.1\r\n\
    Host: api.bonfire-project.eu:444\r\n\
    Accept: */*\r\n\
    Authorization: Basic XXX\r\n\
    Accept-Encoding: gzip, deflate\r\n\
    Content-Type: application/vnd.bonfire+xml; charset=utf-8\r\n\
    \r\n\
    <?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
    <experiment xmlns=\"http://api.bonfire-project.eu/doc/schemas/occi\">\r\n\
      <name>Scenario1</name>\r\n\
      <walltime>1800</walltime>\r\n\
      <description>Demo of scenario1 using Restfully</description>\r\n\
    </experiment>\r\n";

  MyParser parser;

  Request parsed = parser.parseRequest(request, 0);
  printf("\n----------------------------------------------\n");
  Request parsed_body = parser.parseRequest(body_request, 0);

  std::cout << parsed << std::endl;
  std::cout << parsed_body << std::endl;

  return 0;
}

