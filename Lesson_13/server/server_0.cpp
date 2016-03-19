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
#include <unistd.h>  // close()
#include "logger.h"

/**
 * 1. Create a socket with the socket() system call.
 *
 * 2. Bind the socket to an address using the bind() system call. 
 *    For a server socket on the Internet, an address consists of a port number on the host machine.
 *
 * 3. Listen for connections with the listen() system call.
 *
 * 4. Accept a connection with the accept() system call.
 *    This call typically blocks until a client connects with the server.
 *
 * 5. Send and receive data using the read() and write() system calls.
**/

struct ServerException {
  ServerException() {
    ERR("%s", strerror(errno));
  }
};

bool stopped = false;

/// Socket Programming Guide: http://www.beej.us/guide/bgnet/output/html/singlepage/bgnet.html
/// @see http://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
/// Socket: http://man7.org/linux/man-pages/man2/socket.2.html
/// sockaddr_in: https://msdn.microsoft.com/en-us/en-en/library/zx63b042.aspx
/// hton: http://linux.die.net/man/3/htons
/// INADDR_ANY: https://www.cs.cmu.edu/~srini/15-441/F01.full/www/assignments/P2/htmlsim_split/node18.html
///             http://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming-c
class SingleThreadServer {
public:
  SingleThreadServer(int port, int duration);
  ~SingleThreadServer();

  void run();

private:
  int m_port;
  int m_duration;
  int m_socket;  // file descriptor to refer to that endpoint
  sockaddr_in m_address_structure;  // structure to handle connection addresses

  void printClientInfo(sockaddr_in& peeraddr);
  void handleClientMessages(int data_transfer_socket);
};

// ----------------------------------------------
SingleThreadServer::SingleThreadServer(int port, int duration)
  : m_port(port)
  , m_duration(duration)
  , m_socket(socket(PF_INET, SOCK_STREAM, 0)) {  // create an endpoint for communication

  if (m_socket < 0) {
    ERR("Failed to open socket");
    throw ServerException();
  }
  memset(&m_address_structure, 0, sizeof(sockaddr_in));
  m_address_structure.sin_family = AF_INET;  // Quiz: what are relations between AF_INET and PF_INET ?
  m_address_structure.sin_addr.s_addr = htonl(INADDR_ANY);
  m_address_structure.sin_port = htons(m_port);

  if (bind(m_socket, reinterpret_cast<sockaddr*>(&m_address_structure), sizeof(m_address_structure)) < 0) {
    ERR("Failed to bind socket to the address");
    throw ServerException();
  }
}

SingleThreadServer::~SingleThreadServer() {
  close(m_socket);
}

void SingleThreadServer::run() {
  // set the "LINGER" timeout to zero, to close the listen socket
  // immediately at program termination.
  linger linger_opt = { 1, 0 };  // Linger active, timeout 0
  setsockopt(m_socket, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

  listen(m_socket, 20);  // listen for incoming connections, up to 20 pending connection in a queue

  clock_t start = clock();
  clock_t elapsed = start;

  while (elapsed - start < m_duration * CLOCKS_PER_SEC) {  // server loop
    sockaddr_in client_address_structure;
    socklen_t client_address_structure_size = sizeof(client_address_structure);

    // accept one pending connection, waits until a new connection comes
    int data_transfer_socket = accept(m_socket, reinterpret_cast<sockaddr*>(&client_address_structure), &client_address_structure_size);
    if (data_transfer_socket < 0) {
      ERR("Failed to open new socket for data transfer");
      continue;  // skip failed connection
    }

    printClientInfo(client_address_structure);

    std::string hello_message = "Server: connection has been established\n";
    send(data_transfer_socket, hello_message.c_str(), hello_message.length(), 0);

    handleClientMessages(data_transfer_socket);  // start single thread to handle incoming data

    elapsed = clock();
  }
  stopped = true;  // stop handler threads
}

// ----------------------------------------------
void SingleThreadServer::printClientInfo(sockaddr_in& peeraddr) {
  printf("Connection from IP %d.%d.%d.%d, port %d\n",
        (ntohl(peeraddr.sin_addr.s_addr) >> 24) & 0xff, // High byte of address
        (ntohl(peeraddr.sin_addr.s_addr) >> 16) & 0xff, // . . .
        (ntohl(peeraddr.sin_addr.s_addr) >> 8) & 0xff,  // . . .
        ntohl(peeraddr.sin_addr.s_addr) & 0xff,         // Low byte of addr
        ntohs(peeraddr.sin_port));
}

static void workerThread(int data_transfer_socket) {
  int length = 2048;
  char buffer[length];
  char output[length];
  int read_bytes = 0;
  while (!stopped && (read_bytes = recv(data_transfer_socket, buffer, length, 0)) != 0) {
    // process data: here - simply print
    strncpy(output, buffer, read_bytes);
    MSG("Received: %s", output);
  }
}

void SingleThreadServer::handleClientMessages(int data_transfer_socket) {
  std::thread t(workerThread, data_transfer_socket);
  t.detach();
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Server 0");

  int port = 9000;  // default port
  int duration = 20;  // in seconds

  if (argc >= 2) {
    port = std::atoi(argv[1]);
    if (argc >= 3) {
      duration = std::atoi(argv[2]);
    }
  }

  SingleThreadServer server(port, duration);
  server.run();

  DBG("[Lesson 13]: Server 0");
  return 0;
}

