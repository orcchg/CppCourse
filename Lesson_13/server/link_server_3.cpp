#include "all.h"

struct ServerException {};

class Server {
public:
  Server(int port);
  ~Server();

  void run();

private:
  int m_socket;  // file descriptor to refer to that endpoint
  sockaddr_in m_address_structure;  // structure to handle connection addresses
};

// ----------------------------------------------
Server::Server(int port)
  : m_socket(socket(PF_INET, SOCK_STREAM, 0)) {  // create an endpoint for communication

  if (m_socket < 0) {
    ERR("Failed to open socket");
    throw ServerException();
  }
  memset(&m_address_structure, 0, sizeof(sockaddr_in));
  m_address_structure.sin_family = AF_INET;
  m_address_structure.sin_addr.s_addr = htonl(INADDR_ANY);
  m_address_structure.sin_port = htons(port);

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

    //std::string text = "HTTP/1.1 200 OK\r\nContent-length: 300\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body><a href=\"http://mamba.ru/my/access.phtml?oid=1392400874&secret=158.YB8CcjoEWndxg41P&ts=1465310120&mailstat=158_b83ff6b7eb7ac3d1c298523de23ca406&goto=%2Fmy/hit_list.phtml\">First!</a></body>\n</html>\r\n";
    //std::string text = "HTTP/1.1 200 OK\r\nContent-length: 300\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body><a href=\"http://mamba.ru/my/access.phtml?oid=1392400874&secret=158.YB8CcjoEWndxg41P&ts=1465310120&mailstat=158_b83ff6b7eb7ac3d1c298523de23ca406&goto=%2Fmb1288909212\">Second!</a></body>\n</html>\r\n";
    //std::string text = "HTTP/1.1 200 OK\r\nContent-length: 300\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body><a href=\"http://mamba.ru/my/access.phtml?oid=1392400874&secret=158.7NVBX3UCKVoKdPja&ts=1465310120&mailstat=158_b83ff6b7eb7ac3d1c298523de23ca406&goto=%2Fmy/settings_notifications.phtml\">Third!</a></body>\n</html>\r\n";

    std::string text = "HTTP/1.1 200 OK\r\nContent-length: 900\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\n\t<body><a href=\"http://mamba.ru/my/access.phtml?oid=1392400874&secret=158.YB8CcjoEWndxg41P&ts=1465310120&mailstat=158_b83ff6b7eb7ac3d1c298523de23ca406&goto=%2Fmy/hit_list.phtml\">First!</a><a href=\"http://mamba.ru/my/access.phtml?oid=1392400874&secret=158.YB8CcjoEWndxg41P&ts=1465310120&mailstat=158_b83ff6b7eb7ac3d1c298523de23ca406&goto=%2Fmb1288909212\">Second!</a><a href=\"http://mamba.ru/my/access.phtml?oid=1392400874&secret=158.7NVBX3UCKVoKdPja&ts=1465310120&mailstat=158_b83ff6b7eb7ac3d1c298523de23ca406&goto=%2Fmy/settings_notifications.phtml\">Third!</a></body>\n</html>\r\n";
    send(data_transfer_socket, text.c_str(), text.length(), 0);
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Link Server 0");

  int port = 9002;
  if (argc > 1) {
    port = std::atoi(argv[1]);
  }

  Server server(port);
  server.run();

  DBG("[Lesson 13]: Link Server 0 END");
  return 0;
}

