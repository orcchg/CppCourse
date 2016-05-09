#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>  // inet_addr()
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>  // close()
#include "logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 13]: Client 0");

  int port = 9000;  // default port
  char ip_address[16];  // xxx.xxx.xxx.xxx
  strcpy(ip_address, "127.0.0.1\0");

  if (argc >= 2) {
    strcpy(ip_address, argv[1]);
    if (argc >= 3) {
      port = std::atoi(argv[2]);
    }
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in address_structure;
  memset(&address_structure, 0, sizeof(sockaddr_in));
  address_structure.sin_family = AF_INET;
  address_structure.sin_addr.s_addr = inet_addr(ip_address);
  address_structure.sin_port = htons(port);

  connect(sockfd, reinterpret_cast<sockaddr*>(&address_structure), sizeof(address_structure));

  char buffer[1024];
  memset(buffer, 0, 1024);
  recv(sockfd, buffer, 1024, 0);
  INF("Received from Server: %s", buffer);

  bzero(buffer, 1024);
  fgets(buffer, 1024, stdin);
  send(sockfd, buffer, strlen(buffer), 0);

  close(sockfd);

  DBG("[Lesson 13]: Client 0 END");
  return 0;
}

