#ifndef SECURE_CLIENT__H__
#define SECURE_CLIENT__H__

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class SecureClient {
public:
  SecureClient(const std::string& config_file);
  virtual ~SecureClient();

  void run();

private:
  BIO* m_bio;
  SSL_CTX* m_context;
  SSL* m_ssl;

  std::string m_ip_address;
  std::string m_port;

  bool readConfiguration(const std::string& config_file);
};

struct ClientException {};

#endif  // SECURE_CLIENT__H__

