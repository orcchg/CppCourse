#include "secure_server.h"

/// @see http://stackoverflow.com/questions/7698488/turn-a-simple-socket-into-an-ssl-socket

SecureServer::SecureServer() {
  SSL_library_init();
  SSL_load_error_strings();
  ERR_load_crypto_strings();

  m_bio = BIO_new(BIO_s_file());

  auto method = SSLv23_method();
  m_context = SSL_CTX_new(method);
  m_ssl = SSL_new(m_context);


}

SecureServer::~SecureServer() {
}

void SecureServer::run() {
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  SecureServer server;
  server.run();
  return 0;
}

