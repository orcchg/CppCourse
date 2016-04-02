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

// --------------------------------------------------------------------------------------------------------------------
/**
 * Response:

"Response: HTTP/1.1 200 OK
Access-Control-Allow-Headers: X-Requested-With
Access-Control-Allow-Origin: *
Content-Type: text/html; charset=UTF-8
Date: Sat, 02 Apr 2016 19:21:00 GMT
Server: Apache/2.4.6 (CentOS) PHP/5.4.16
Vary: User-Agent
X-Powered-By: PHP/5.4.16
Transfer-Encoding: chunked

480
<!DOCTYPE html>
<!--[if IE 8]><html class="ie ie8"> <![endif]-->
<!--[if IE 9]><html class="ie ie9"> <![endif]-->
<!--[if gt IE 9]><!-->	<html> <!--<![endif]-->
<head>
<!-- Basic -->
<meta charset="utf-8">
<title>HTTP Message Examples</title>
<meta name="description" content="HTTP Message Examples - Learn HTTP Protocol (Hypertext, Transfer, Protocol based on RFC 2616) in simple and easy steps starting from its simple overview, protocol parameters, message architecture, requests, responses, connection, caching, status codes, header fields, security  and methods like GET, POST, HEAD, PUT along with suitable examples." />
<meta name="keywords" content="Hypertext, Transfer, Protocol, HTTP, Tutorial, Message Codes, HTTP Header, Response, Client , Server, Request Line, Message Body, HTTP Example, Methods, GET, POST, HEAD, PUT, Proxies, Version, RFC 2616" />
<base href="http://www.tutorialspoint.com/" />
<link rel="shortcut icon" href="/favicon.ico" type="image/x-icon" />
<meta name="viewport" content="width=device-width,initial-scale=1.0,user-scalable=yes">
<meta property="og:locale" content="en_US" />
<meta property="og:type" content="
1699
website" />
<meta property="fb:app_id" content="471319149685276" />
<meta property="og:site_name" content="www.tutorialspoint.com" />
<meta name="robots" content="index, follow"/>
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black">
<meta name="author" content="tutorialspoint.com">
<script type="text/javascript" src="/theme/js/script-min-v4.js"></script>
<link rel="stylesheet" href="/theme/css/style-min.css">
<!-- Head Libs -->
<!--[if IE 8]>
<link rel="stylesheet" type="text/css" href="/theme/css/ie8.css`@"

**/

