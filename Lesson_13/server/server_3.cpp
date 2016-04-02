#include "all.h"

/**
 * HTTP Protocol
 *
 * @see http://www.tutorialspoint.com/http/index.htm
 * @see http://www.tutorialspoint.com/http/http_message_examples.htm
 *
 * 1. start line (required)
 * 2. header lines (0 or more)
 * 3. blank line (CRLF)
 * 4. body (optional)
 */

// ----------------------------------------------
/**
 * HTTP Server
 *
 * @see https://www.jmarshall.com/easy/http/
 *
 * HTTP 1.0 is a stateless protocol - it not maintaining any connection information
 * between transactions. After delivering the response to an HTTP Client, the 
 * HTTP Server always closes an established connection.
 *
 * HTTP 1.1 could specify 'Persistent connection' or 'Connection close' headers
 * indicating whether to maintain an established connection between requests or
 * close it right after delivering. Thus, several requests / responses could be sent
 * through single persistent connection. Connections are considered persistent
 * in HTTP 1.1 by default.
 */

#define PORT_NUMBER 80

struct ServerException {
  ServerException() {
    ERR("%s", strerror(errno));
  }
};

class Server {
public:
  Server();
  ~Server();

  void run();

private:
  int m_socket;  // file descriptor to refer to that endpoint
  sockaddr_in m_address_structure;  // structure to handle connection addresses

  void printClientInfo(sockaddr_in& peeraddr);
  void handleClientMessages(int data_transfer_socket);
};

// ----------------------------------------------
Server::Server()
  : m_socket(socket(PF_INET, SOCK_STREAM, 0)) {  // create an endpoint for communication

  if (m_socket < 0) {
    ERR("Failed to open socket");
    throw ServerException();
  }
  memset(&m_address_structure, 0, sizeof(sockaddr_in));
  m_address_structure.sin_family = AF_INET;
  m_address_structure.sin_addr.s_addr = htonl(INADDR_ANY);
  m_address_structure.sin_port = htons(PORT_NUMBER);

  if (bind(m_socket, reinterpret_cast<sockaddr*>(&m_address_structure), sizeof(m_address_structure)) < 0) {
    ERR("Failed to bind socket to the address");
    throw ServerException();
  }
}

Server::~Server() {
  close(m_socket);
}

void Server::run() {
  // set the "LINGER" timeout to zero, to close the listen socket
  // immediately at program termination.
  linger linger_opt = { 1, 0 };  // Linger active, timeout 0
  setsockopt(m_socket, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

  listen(m_socket, 20);  // listen for incoming connections, up to 20 pending connection in a queue

  while (true) {  // server loop
    sockaddr_in client_address_structure;
    socklen_t client_address_structure_size = sizeof(client_address_structure);

    // accept one pending connection, waits until a new connection comes
    int data_transfer_socket = accept(m_socket, reinterpret_cast<sockaddr*>(&client_address_structure), &client_address_structure_size);
    if (data_transfer_socket < 0) {
      ERR("Failed to open new socket for data transfer");
      continue;  // skip failed connection
    }

    printClientInfo(client_address_structure);

    // TODO[Quiz]: What if Server's response doesn't fit HTTP protocol?
    // std::string hello_message = "Server: connection has been established\n";
    // send(data_transfer_socket, hello_message.c_str(), hello_message.length(), 0);

    handleClientMessages(data_transfer_socket);  // start single thread to handle incoming data
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

/**
 * Server response:
 *
 * HTTP/1.1 200 OK
 * Content-Length: 56
 * Content-Type: text/html
 * Connection: Closed
 * 
 * <html>
 *    <body>
 *        <h1>Hello, World!</h1>
 *    </body>
 * </html>
 */

static void workerThread(int socket) {
  int length = 2048;
  char buffer[length];
  char output[length];
  int read_bytes = 0;
  while ((read_bytes = recv(socket, buffer, length, 0)) != 0) {
    // process data: here - simply print
    strncpy(output, buffer, read_bytes);
    MSG("Received: %s", output);

    // send response
    std::string text = "HTTP/1.1 200 OK\r\nContent-length: 56\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body>\n\t\t<h1>Hello, World!</h1>\n\t</body>\n</html>\r\n";
    send(socket, text.c_str(), text.length(), 0);
    DBG("Sent: %s", text.c_str());
  }
}

void Server::handleClientMessages(int data_transfer_socket) {
  std::thread t(workerThread, data_transfer_socket);
  t.detach();
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Server 3");

  Server server;
  server.run();

  DBG("[Lesson 13]: Server 3 END");
  return 0;
}

