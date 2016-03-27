#include <thread>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>  // inet_addr()
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>  // close()
#include "logger.h"

static void usage() {
  printf("Usage: client <id> <to> [ip_address] [port]\n");
}

/**
 * Client-Server protocol:
 *
 * client_id#dest_client_id\0   ; length - up to 32 bytes
 */

static void receiverThread(int sockfd) {
  char buffer[1024];
  recv(sockfd, buffer, 1024, 0);
  printf("message: %s\n", buffer);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Client 1");

  int client_id = -1;  // specify client id at begin
  int dest_client_id = -1;  // specify destination client id
  int port = 9000;  // default port
  char ip_address[16];  // xxx.xxx.xxx.xxx
  strcpy(ip_address, "127.0.0.1\0");

  if (argc >= 3) {
    client_id = std::atoi(argv[1]);
    dest_client_id = std::atoi(argv[2]);
    if (argc >= 4) {
      strcpy(ip_address, argv[3]);
      if (argc >= 5) {
        port = std::atoi(argv[4]);
      }
    }
  } else {
    ERR("You must specify client id and destination client id at begin");
    usage();
    return 1;
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in address_structure;
  memset(&address_structure, 0, sizeof(sockaddr_in));
  address_structure.sin_family = AF_INET;
  address_structure.sin_addr.s_addr = inet_addr(ip_address);
  address_structure.sin_port = htons(port);

  connect(sockfd, reinterpret_cast<sockaddr*>(&address_structure), sizeof(address_structure));

  // sending client id and destination client id
  std::string payload = std::to_string(client_id) + std::string("#") + std::to_string(dest_client_id);
  send(sockfd, payload.c_str(), payload.size(), 0);

  char buffer[1024];
  recv(sockfd, buffer, 1024, 0);
  INF("Received from Server: %s", buffer);

  // listen for incoming messages
  std::thread t(receiverThread, sockfd);
  t.detach();

  do {
    bzero(buffer, 1024);
    fgets(buffer, 1024, stdin);
    send(sockfd, buffer, strlen(buffer), 0);
  } while (strlen(buffer) > 1);

  close(sockfd);

  DBG("[Lesson 13]: Client 1 END");
  return 0;
}

