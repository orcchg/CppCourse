#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "logger.h"

// const char* URL_CATAPI = "http://thecatapi.com/api/images/get?format=xml&results_per_page=3";

/// @see http://www.tutorialspoint.com/http/http_message_examples.htm

static char* prepareHttpRequest() {
  char* request = new char[2048];

  // TODO[Quiz]: make some http requests manually

  std::string text = "GET /http/http_message_examples.htm HTTP/1.1\r\nHost: www.tutorialspoint.com\r\nFrom: orcchg@yandex.ru\r\nUser-Agent: CppCourse_Lesson_13_Http_3/1.1\r\nAccept-Language: en-us\r\nAccept-Encoding: gzip, deflate\r\nConnection: Keep-Alive\r\n\r\n";

  // std::string text = "GET /wiki/HTTP HTTP/1.0\r\nHost: ru.wikipedia.org\r\n\r\n";

  strncpy(request, text.c_str(), text.length());
  MSG("Request: %s", request);

  return request;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Http 3");

  addrinfo hints;
  addrinfo* server_info;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo("www.tutorialspoint.com", "http", &hints, &server_info);  // http - default port 80, because port is not specified
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

  char response[2048];  // TODO[Quiz]: this could not enough space - enlarge if necessary
  recv(sockfd, response, 2048, 0);
  INF("Response: %s", response);

  close(sockfd);

  DBG("[Lesson 13]: Http 3 END");
  return 0;
}

