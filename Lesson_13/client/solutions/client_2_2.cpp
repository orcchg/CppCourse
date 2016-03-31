#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "logger.h"
#include "protocol_0.h"

#define MESSAGE_SIZE 4096
#define END_STRING "!@#$\0"

bool is_stopped = false;

/* Tools */
// ----------------------------------------------------------------------------
static void usage() {
  printf("client_2 <server.cfg>\n");
}

static long long hash(const std::string& str) {
  srand(clock());

  // Java String hash code: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
  int prime = 7;
  long long hash = 0;
  int power = str.length() - 1;

  for (auto it = str.begin(); it != str.end(); ++it, --power) {
    hash += static_cast<long long>(*it) * std::pow(prime, power) + rand() % 100 + 1;
  }
  return hash;
}

static std::string enterName() {
  printf("Enter name: ");
  std::string name;
  std::cin >> name;
  return name;
}

long long getCurrentTime() {
  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  return millis;
}

struct ClientException {};

/* Worker thread */
// ----------------------------------------------------------------------------
static void receiverThread(int sockfd) {
  while (true) {
    char buffer[MESSAGE_SIZE];
    recv(sockfd, buffer, MESSAGE_SIZE, 0);

    // check for termination
    if (strncmp(buffer, END_STRING, strlen(END_STRING)) == 0) {
      INF("Server: connection closed");
      is_stopped = true;  // stop main loop
      return;  // Server has sent end signal
    }

    Protocol proto = deserialize(buffer);

    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::ostringstream oss;
    oss << std::ctime(&end_time);

    printf("%s :: %s: %s\n", oss.str().c_str(), proto.name.c_str(), proto.message.c_str());
  }
}

/* Client */
// ----------------------------------------------------------------------------
class Client {
public:
  Client(long long id, const std::string& name);
  ~Client();

  void init(const std::string& config_file);
  void run();

private:
  long long m_id;
  std::string m_name;

  std::string m_ip_address;
  std::string m_port;

  int m_socket;
  bool m_is_connected;

  bool readConfiguration(const std::string& config_file);
};

Client::Client(long long id, const std::string& name)
  : m_id(id), m_name(name) {
  MSG("Initialized client with name %s and id %lli", name.c_str(), id);
}

Client::~Client() {
  close(m_socket);
}

void Client::init(const std::string& config_file) {
  if (!readConfiguration(config_file)) {
    throw ClientException();
  }

  // prepare address structure
  addrinfo hints;
  addrinfo* server_info;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(m_ip_address.c_str(), m_port.c_str(), &hints, &server_info);
  if (status != 0) {
    ERR("Failed to prepare address structure: %s", gai_strerror(status));  // see error message
    throw ClientException();
  }

  // establish connection
  addrinfo* ptr = server_info;

  for (; ptr != nullptr; ptr = ptr->ai_next) {  // loop through all the results
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      continue;  // failed to get connection socket
    }
    if (connect(m_socket, server_info->ai_addr, server_info->ai_addrlen) == -1) {
      close(m_socket);
      continue;  // failed to connect to a particular server
    }
    break;  // connect to the first particular server we can
  }

  if (ptr == nullptr) {
    ERR("Failed to connect to Server");
    m_is_connected = false;
  } else {
    m_is_connected = true;
  }

  freeaddrinfo(server_info);  // release address stucture and remove from linked list

  if (m_is_connected) {
    // register to Server
    Protocol proto;
    proto.src_id = m_id;
    proto.name = m_name;
    char* raw_proto = serialize(proto);
    send(m_socket, raw_proto, strlen(raw_proto), 0);
    delete [] raw_proto;
  }
}

void Client::run() {
  if (!m_is_connected) {
    ERR("No connection established to Server");
    throw ClientException();
  }

  // get response from Server
  char buffer[256];
  recv(m_socket, buffer, 256, 0);
  INF("Server response: %s", buffer);

  // run message receiver thread
  std::thread t(receiverThread, m_socket);
  t.detach();

  // send messages loop
  std::string message;
  while (!is_stopped && getline(std::cin, message)) {
    Protocol proto;
    proto.src_id = m_id;
    proto.timestamp = getCurrentTime();
    proto.name = m_name;
    proto.message = message;

    char* raw_proto = serialize(proto);
    send(m_socket, raw_proto, strlen(raw_proto), 0);
    delete [] raw_proto;
  }
}

// ----------------------------------------------
bool Client::readConfiguration(const std::string& config_file) {
  bool result = true;

  std::fstream fs;
  fs.open(config_file, std::fstream::in);

  if (fs.is_open()) {
    std::string line;
    
    // ip address
    std::getline(fs, line);
    int i1 = line.find_first_of(' ');
    m_ip_address = line.substr(i1 + 1);
    DBG("IP address: %s", m_ip_address.c_str());

    // port
    std::getline(fs, line);
    int i2 = line.find_first_of(' ');
    m_port = line.substr(i2 + 1);
    DBG("Port: %s", m_port.c_str());

    fs.close();
  } else {
    ERR("Failed to open configure file: %s", config_file.c_str());
    result = false;
  }

  return result;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Client 2.2");

  std::string config_file = "../data/server.cfg";
  if (argc >= 2) {
    char buffer[256];
    strncpy(buffer, argv[1], strlen(argv[1]));
    config_file = std::string(buffer);
  }
  DBG("Configuration from file: %s", config_file.c_str());

  std::string name = enterName();
  long long id = hash(name);

  Client client(id, name);
  client.init(config_file);
  client.run();

  DBG("[Lesson 13]: Client 2.2 END");
  return 0;
}

