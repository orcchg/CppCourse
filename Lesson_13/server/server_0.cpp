#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include "logger.h"

/// @see http://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
class SingleThreadServer {
public:
  SingleThreadServer(int port, int duration);

  void run();

private:
  int m_port;
  int m_duration;

  void loop();
};

// ----------------------------------------------
SingleThreadServer::SingleThreadServer(int port, int duration)
  : m_port(port), m_duration(duration) {
}

void SingleThreadServer::run() {

}

void SingleThreadServer::loop() {

}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Server 0");

  int port = 9000;
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

