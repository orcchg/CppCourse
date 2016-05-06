#ifndef SECURE_SERVER__H__
#define SECURE_SERVER__H__

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/// @see http://h71000.www7.hp.com/doc/83final/ba554_90007/ch04s03.html

class SecureServer {
public:
  SecureServer();
  virtual ~SecureServer();

private:
  SSL_CTX* m_context;
  SSL* m_ssl;
};

#endif  // SECURE_SERVER__H__

