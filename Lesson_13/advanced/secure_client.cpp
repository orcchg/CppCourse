#include "all.h"
#include "logger.h"
#include "secure_client.h"

#define MESSAGE_SIZE 4096

/// @see http://fm4dd.com/openssl/sslconnect.htm

SecureClient::SecureClient(const std::string& config_file) {
  if (!readConfiguration(config_file)) {
    throw ClientException();
  }

  SSL_load_error_strings();
  ERR_load_BIO_strings();
  OpenSSL_add_all_algorithms();

  m_context = SSL_CTX_new(SSLv23_client_method());
  if (!SSL_CTX_load_verify_locations(m_context, "../data/ca-cert.pem", nullptr)) {
    WRN("Failed to load Trust Store certificates");
    // connection can still continue
  }

  m_bio = BIO_new_ssl_connect(m_context);
  if (m_bio == nullptr) {
    ERR("Failed to setup connection");
    throw ClientException();
  }
  BIO_get_ssl(m_bio, &m_ssl);
  SSL_set_mode(m_ssl, SSL_MODE_AUTO_RETRY);
  BIO_set_conn_hostname(m_bio, m_ip_address.c_str());
  BIO_set_conn_port(m_bio, m_port.c_str());

  if (BIO_do_connect(m_bio) <= 0) {
    ERR("Failed to open connection");
    throw ClientException();
  }

  if (SSL_get_verify_result(m_ssl) != X509_V_OK) {
    WRN("Certificate verification failed");
    // connection can still continue
  }
}

SecureClient::~SecureClient() {
  SSL_CTX_free(m_context);
  BIO_free_all(m_bio);
}

void SecureClient::run() {
  char buffer[MESSAGE_SIZE];
  memset(buffer, 0, MESSAGE_SIZE);
  int read_bytes = BIO_read(m_bio, buffer, MESSAGE_SIZE);
  INF("Response: %.*s", read_bytes, buffer);

  std::string message = "Hello, Mr. Server!";
  BIO_write(m_bio, message.c_str(), message.length());
}

// ----------------------------------------------
bool SecureClient::readConfiguration(const std::string& config_file) {
  bool result = true;

  std::fstream fs;
  fs.open(config_file, std::fstream::in);

  if (fs.is_open()) {
    std::string line;
    
    // ip address
    std::getline(fs, line);
    int i1 = line.find_first_of(' ');
    m_ip_address = line.substr(i1 + 1);
    // m_ip_address = inet_addr(ip_address_str.c_str());

    // port
    std::getline(fs, line);
    int i2 = line.find_first_of(' ');
    m_port = line.substr(i2 + 1);
    // m_port = htons(std::atoi(port_str.c_str()));

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
  std::string config_file = "../data/server.cfg";
  if (argc >= 2) {
    char buffer[256];
    strncpy(buffer, argv[1], strlen(argv[1]));
    config_file = std::string(buffer);
  }
  DBG("Configuration from file: %s", config_file.c_str());

  SecureClient client(config_file);
  client.run();

  return 0;
}

