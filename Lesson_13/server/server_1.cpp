#include <map>
#include <string>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "logger.h"

struct ServerException {
  ServerException() {
    ERR("%s", strerror(errno));
  }
};

struct Peer {
  int dest_id;
  int socket;

  Peer();
  Peer(int dest_id, int socket);
};

Peer::Peer() {
}

Peer::Peer(int dest_id, int socket)
  : dest_id(dest_id), socket(socket) {
}

/* Server */
// ----------------------------------------------------------------------------
class PeerServer {
public:
  PeerServer();
  ~PeerServer();

  void run();

  Peer* getPeer(int client_id);

private:
  int m_socket;
  std::map<int, Peer> m_clients_map;

  void printClientInfo(sockaddr_in& peeraddr);
  void handleClientMessages(int client_id, int data_transfer_socket);
};

PeerServer::PeerServer()
  : m_socket(socket(PF_INET, SOCK_STREAM, 0)) {

  if (m_socket < 0) {
    ERR("Failed to open socket");
    throw ServerException();
  }

  int port = 9000;
  sockaddr_in address_structure;

  memset(&address_structure, 0, sizeof(sockaddr_in));
  address_structure.sin_family = AF_INET;
  address_structure.sin_addr.s_addr = htonl(INADDR_ANY);
  address_structure.sin_port = htons(port);

  if (bind(m_socket, reinterpret_cast<sockaddr*>(&address_structure), sizeof(address_structure)) < 0) {
    ERR("Failed to bind socket to the address");
    throw ServerException();
  }
}

PeerServer::~PeerServer() {
  close(m_socket);
}

Peer* PeerServer::getPeer(int client_id) {
  auto it = m_clients_map.find(client_id);
  if (it != m_clients_map.end()) {
    return &it->second;
  }
  return nullptr;
}

// ----------------------------------------------
void PeerServer::run() {
  linger linger_opt = { 1, 0 };  // Linger active, timeout 0
  setsockopt(m_socket, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

  listen(m_socket, 20);

  while (true) {  // server loop
    sockaddr_in client_address_structure;
    socklen_t client_address_structure_size = sizeof(client_address_structure);

    // accept one pending connection, waits until a new connection comes
    int data_transfer_socket = accept(m_socket, reinterpret_cast<sockaddr*>(&client_address_structure), &client_address_structure_size);
    if (data_transfer_socket < 0) {
      ERR("Failed to open new socket for data transfer");
      continue;  // skip failed connection
    }

    // get incoming client
    printClientInfo(client_address_structure);
    char buf[32];
    recv(data_transfer_socket, buf, 32, 0);
    std::string input_str = std::string(buf);
    int delimiter_index = input_str.find_first_of("#");
    int client_id = std::atoi(input_str.substr(0, delimiter_index).c_str());
    int dest_client_id = std::atoi(input_str.substr(delimiter_index + 1).c_str());
    m_clients_map[client_id] = Peer(dest_client_id, data_transfer_socket);
    INF("Client [id = %i] has connected, destination client id: %i", client_id, dest_client_id);

    // send confirmation to client
    std::string hello_message = "Server: connection has been established\n\0";
    send(data_transfer_socket, hello_message.c_str(), hello_message.length(), 0);

    handleClientMessages(client_id, data_transfer_socket);  // start single thread to handle incoming data
  }
}

// ----------------------------------------------
void PeerServer::printClientInfo(sockaddr_in& peeraddr) {
  printf("Connection from IP %d.%d.%d.%d, port %d\n",
        (ntohl(peeraddr.sin_addr.s_addr) >> 24) & 0xff, // High byte of address
        (ntohl(peeraddr.sin_addr.s_addr) >> 16) & 0xff, // . . .
        (ntohl(peeraddr.sin_addr.s_addr) >> 8) & 0xff,  // . . .
        ntohl(peeraddr.sin_addr.s_addr) & 0xff,         // Low byte of addr
        ntohs(peeraddr.sin_port));
}

static void workerThread(PeerServer* server, int client_id, int data_transfer_socket) {
  int length = 2048;
  char buffer[length];
  char output[length];
  int read_bytes = 0;
  while ((read_bytes = recv(data_transfer_socket, buffer, length, 0)) != 0) {
    // process data: here - simply print
    strncpy(output, buffer, read_bytes);
    MSG("Received [size = %i]: %s", read_bytes, output);

    // transfer from source peer to destination peer
    Peer* client_peer = server->getPeer(client_id);
    Peer* dest_peer = server->getPeer(client_peer->dest_id);
    if (dest_peer != nullptr) {
      int dest_socket = dest_peer->socket;
      send(dest_socket, buffer, strlen(buffer), 0);
    } else {
      WRN("Destination peer [id = %i] not connected", client_peer->dest_id);
    }
  }
}

void PeerServer::handleClientMessages(int client_id, int data_transfer_socket) {
  std::thread t(workerThread, this, client_id, data_transfer_socket);
  t.detach();
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Server 1");

  PeerServer server;
  server.run();

  DBG("[Lesson 13]: Server 1 END");
  return 0;
}

