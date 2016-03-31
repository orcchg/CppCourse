#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
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
#include "protocol_0.h"

#define PORT_NUMBER 9000
#define MESSAGE_SIZE 4096
#define END_STRING "!@#$\0"

bool is_stopped = false;

/* Tools */
// ----------------------------------------------------------------------------
static void printHelp() {
  printf("Commands:\n\thelp - print this help \
                   \n\tstop - send terminate signal to all peers and stop server\n");
}

static void stopServer() {
  is_stopped = true;
}

struct Peer {
  int id;
  int socket;
  std::string name;
};

struct ServerException {};

/* Interface */
// ----------------------------------------------------------------------------
const char* HELP = "help";
const char* STOP = "stop";

bool evaluate(char* command) {
  if (strcmp(HELP, command) == 0) {
    printHelp();
  } else if (strcmp(STOP, command) == 0) {
    stopServer();
    return false;
  } else {
    WRN("Undefined command: %s", command);
  }
  return true;
}

/* Server */
// ----------------------------------------------------------------------------
class Server {
public:
  Server();
  ~Server();

  void run();

private:
  int m_socket;
  std::unordered_map<int, Peer> m_peers;

  void runListener();

  void printClientInfo(sockaddr_in& peeraddr);
  Protocol getIncomingMessage(int socket);
  bool registerClientIfNeed(const Protocol& proto, int socket, sockaddr_in address_structure);
  void processMessages(int socket);
};

Server::Server()
  : m_socket(socket(PF_INET, SOCK_STREAM, 0)) {

  if (m_socket < 0) {
    ERR("Failed to open socket");
    throw ServerException();
  }

  int port = PORT_NUMBER;

  // prepare address structure
  sockaddr_in address_structure;
  memset(&address_structure, 0, sizeof(sockaddr_in));
  address_structure.sin_family = AF_INET;
  address_structure.sin_addr.s_addr = htonl(INADDR_ANY);
  address_structure.sin_port = htons(port);

  // bind socket with address structure
  if (bind(m_socket, reinterpret_cast<sockaddr*>(&address_structure), sizeof(address_structure)) < 0) {
    ERR("Failed to bind socket to the address");
    throw ServerException();
  }

  // when the socket of a type that promises reliable delivery still has untransmitted messages when it is closed
  linger linger_opt = { 1, 0 };  // timeout 0 seconds - close socket immediately
  setsockopt(m_socket, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

  // listen for incoming connections
  listen(m_socket, 20);
}

Server::~Server() {
  // broadcast close signal to all peers
  for (auto it = m_peers.begin(); it != m_peers.end(); ++it) {
    char end_signal[MESSAGE_SIZE];
    strncpy(end_signal, END_STRING, strlen(END_STRING));
    send(it->second.socket, end_signal, strlen(end_signal), 0);
    close(it->second.socket);
  }
  close(m_socket);
}

void Server::run() {
  std::thread t(&Server::runListener, this);
  t.detach();

  printHelp();

  // evaluate user commands
  char command[5];
  do {
    printf("server@server:");
    scanf("%s", command);
  } while (evaluate(command));
}

void Server::runListener() {
  while (!is_stopped) {  // server loop
    sockaddr_in peer_address_structure;
    socklen_t peer_address_structure_size = sizeof(peer_address_structure);

    // accept one pending connection, waits until a new connection comes
    int peer_socket = accept(m_socket, reinterpret_cast<sockaddr*>(&peer_address_structure), &peer_address_structure_size);
    if (peer_socket < 0) {
      ERR("Failed to open new socket for data transfer");
      continue;  // skip failed connection
    }

    // get incoming message
    Protocol proto = getIncomingMessage(peer_socket);

    // register incoming Client if not already registered
    if (registerClientIfNeed(proto, peer_socket, peer_address_structure)) {
      // process message in separate thread
      std::thread worker_thread(&Server::processMessages, this, peer_socket);
      worker_thread.detach();
    }
  }
}

// ----------------------------------------------
void Server::printClientInfo(sockaddr_in& peeraddr) {
  printf("Connection from IP %d.%d.%d.%d, port %d\n",
        (ntohl(peeraddr.sin_addr.s_addr) >> 24) & 0xff, // High byte of address
        (ntohl(peeraddr.sin_addr.s_addr) >> 16) & 0xff, // . . .
        (ntohl(peeraddr.sin_addr.s_addr) >> 8) & 0xff,  // . . .
        ntohl(peeraddr.sin_addr.s_addr) & 0xff,         // Low byte of addr
        ntohs(peeraddr.sin_port));
}

Protocol Server::getIncomingMessage(int socket) {
  char buffer[MESSAGE_SIZE];
  int read_bytes = recv(socket, buffer, MESSAGE_SIZE, 0);
  Protocol proto = EMPTY_MESSAGE;  // empty message
  if (read_bytes != 0) {
    proto = deserialize(buffer);
    std::cout << proto << std::endl;
  }
  return proto;
}

bool Server::registerClientIfNeed(const Protocol& proto, int socket, sockaddr_in address_structure) {
  bool result = false;
  auto it_peer = m_peers.find(proto.src_id);

  if (it_peer == m_peers.end()) {  // Client's not been registered yet
    result = true;
    printClientInfo(address_structure);

    Peer peer;
    peer.id = proto.src_id;
    peer.socket = socket;
    peer.name = proto.name;
    m_peers.insert(it_peer, std::pair<int, Peer>(proto.src_id, peer));
    INF("Peer registered: id = %i, name = %s", peer.id, peer.name.c_str());

    // send confirmation to Client
    std::string confirm_message = "Server: peer registered\n\0";
    send(socket, confirm_message.c_str(), confirm_message.length(), 0);
  }

  return result;
}

void Server::processMessages(int socket) {
  Protocol proto;
  while (!is_stopped && (proto = getIncomingMessage(socket)) != EMPTY_MESSAGE) {
    // DBG("Received message: %s", proto.message.c_str());
    // broadcast message to all existing peers (one-channel chat)
    for (auto it = m_peers.begin(); it != m_peers.end(); ++it) {
      if (it->first != proto.src_id) {
        char* raw_message = serialize(proto);
        send(it->second.socket, raw_message, strlen(raw_message), 0);
        delete [] raw_message;
      } else {
        // ignore message from same peer
      }
    }
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Server 2.1");

  Server server;
  server.run();

  DBG("[Lesson 13]: Server 2.1 END");
  return 0;
}

