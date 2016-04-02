#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "http_parser.h"
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

/* Parse http */
// ----------------------------------------------------------------------------
int url_callback(http_parser*, const char *at, size_t length);
int header_field_callback(http_parser*, const char *at, size_t length);
int body_callback(http_parser*, const char *at, size_t length);

class Parser {
public:
  Parser();
  ~Parser();

  void parse(char* http, int nbytes);

private:
  http_parser* m_parser;
  http_parser_settings m_settings;
};

Parser::Parser()
  : m_parser((http_parser*) malloc(sizeof(http_parser))) {

  m_settings.on_url = url_callback;
  m_settings.on_header_field = header_field_callback;
  m_settings.on_body = body_callback;

  http_parser_init(m_parser, HTTP_RESPONSE);
}

Parser::~Parser() {
  free(m_parser);
}

void Parser::parse(char* http, int nbytes) {
  int nparsed = http_parser_execute(m_parser, &m_settings, http, nbytes);
  if (nparsed != nbytes) {
    ERR("Parse error! expected size = %i, actual size = %i, %s", nbytes, nparsed, http);
    throw ParseException();
  }
}

/* Callbacks */
// ----------------------------------------------
int url_callback(http_parser*, const char *at, size_t length) {
  DBG("URL[%zu]: %.*s", length, (int) length, at);
}

int header_field_callback(http_parser*, const char *at, size_t length) {
  DBG("Header[%zu]: %.*s", length, (int) length, at);
}

int header_value_callback(http_parser*, const char *at, size_t length) {
  DBG("Value[%zu]: %.*s", length, (int) length, at);
}

int body_callback(http_parser*, const char *at, size_t length) {
  DBG("Body[%zu]: %.*s", length, (int) length, at);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Http 3.2.exp");

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

  http_parser_settings settings;
  settings.on_url = url_callback;
  settings.on_header_field = header_field_callback;
  settings.on_header_value = header_value_callback;
  settings.on_body = body_callback;
  http_parser* parser = (http_parser*) malloc(sizeof(http_parser));
  http_parser_init(parser, HTTP_RESPONSE);
  //parser->data = (void*) sockfd;

  char response[BUFFER_LENGTH];
  int nbytes = recv(sockfd, response, BUFFER_LENGTH, 0);
  INF("Response: %s", response);

  try {
    int nparsed = http_parser_execute(parser, &settings, response, nbytes);
    if (nparsed != nbytes) {
      ERR("Parse error! expected size = %i, actual size = %i", nbytes, nparsed);
      throw ParseException();
    }
  } catch (ParseException exception) {
    WRN("Failed to parse a response, go on and close connection");
  }

  free(parser);
  close(sockfd);

  DBG("[Lesson 13]: Http 3.2.exp END");
  return 0;
}

