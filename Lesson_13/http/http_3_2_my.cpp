#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "my_parser.h"
#include "logger.h"

#define BUFFER_LENGTH 80 * 1024
#define HOSTNAME "thecatapi.com"

// const char* URL_CATAPI = "http://thecatapi.com/api/images/get?format=xml&results_per_page=3";

struct ParseException {};

static char* prepareHttpRequest() {
  char* request = new char[2048];

  std::string text = "GET /api/images/get?format=xml&results_per_page=3 HTTP/1.1\r\nHost: " HOSTNAME "\r\n\r\n";

  strncpy(request, text.c_str(), text.length());
  MSG("Request: %s", request);

  return request;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Http 3.2.my");

  addrinfo hints;
  addrinfo* server_info;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(HOSTNAME, "http", &hints, &server_info);  // http - default port 80, because port is not specified
  if (status != 0) {
    ERR("Failed to prepare address structure: %s", gai_strerror(status));
    return 1;
  }

  // establish connection
  int sockfd = -1;
  addrinfo* ptr = server_info;

  for (; ptr != nullptr; ptr = ptr->ai_next) {  // loop through all the results
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      continue;  // failed to get connection socket
    }
    if (connect(sockfd, server_info->ai_addr, server_info->ai_addrlen) == -1) {
      close(sockfd);
      continue;  // failed to connect to a particular server
    }
    break;  // connect to the first particular server we can
  }

  if (ptr == nullptr) {
    ERR("Failed to connect to Server");
    return 2;
  }

  char* request = prepareHttpRequest();
  send(sockfd, request, strlen(request), 0);
  delete [] request;

  MyParser parser;

  char response[BUFFER_LENGTH];
  int nbytes = recv(sockfd, response, BUFFER_LENGTH, 0);
  INF("Response: %s", response);

  try {
    // TODO[Quiz]: implement function:  parser.parseResponse(response, nbytes);
  } catch (ParseException exception) {
    WRN("Failed to parse a response, go on and close connection");
  }

  close(sockfd);

  DBG("[Lesson 13]: Http 3.2.my END");
  return 0;
}

