#include "all.h"

struct ServerException {};

class Server {
public:
  Server();
  ~Server();

  void run();

private:
  int m_socket;  // file descriptor to refer to that endpoint
  sockaddr_in m_address_structure;  // structure to handle connection addresses
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
  m_address_structure.sin_port = htons(9000);

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

    //std::string text = "HTTP/1.1 200 OK\r\nContent-length: 73\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body><a href=\"http://client.mamba.ru/real/5555\">OpenMambaApp!</a></body>\n</html>\r\n";
    //std::string text = "HTTP/1.1 200 OK\r\nContent-length: 72\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body><a href=\"http://love.yonja.com/real/5555\">OpenMambaApp!</a></body>\n</html>\r\n";
    std::string text = "HTTP/1.1 200 OK\r\nContent-length: 131\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body><a href=\"http://android.mamba.ru/real/5555\">Mamba</a>\n\n\n<a href=\"http://android.yonja.com/real/5555\">Yonja</a></body>\n</html>\r\n";
    send(data_transfer_socket, text.c_str(), text.length(), 0);
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Link Server 0");

  Server server;
  server.run();

  DBG("[Lesson 13]: Link Server 0 END");
  return 0;
}

