#include "secure_server.h"

SecureServer::SecureServer() {
  SSL_library_init();  // load encryption & hash algos
  SSL_load_error_strings();  // load human-readable error strings
  auto method = SSLv23_method();  // choose protocol version
  m_context = SSL_CTX_new(method);
  SSL_CTX_use_certificate_file(m_context, "path", type);  // own certificate
  //
}

SecureServer::~SecureServer() {
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {

  return 0;
}

