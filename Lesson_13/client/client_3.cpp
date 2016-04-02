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
 * HTTP Client
 *
 * @see https://www.jmarshall.com/easy/http/
 *
 * HTTP 1.0 is a stateless protocol - it not maintaining any connection information
 * between transactions. HTTP Client opens a new connection each time it needs to
 * send a request to the HTTP Server (HTTP transaction).
 *
 * HTTP 1.1 supports persistent connections by default. But Client's request
 * could contain 'Connection: close' header and such connection will be closed
 * after the corresponding response. Server's response may also contain such
 * headers and this means it closes connection after sending a response.
 */

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Client 3");

  std::ostringstream sout;
  sout << curlpp::options::Url("http://127.0.0.1/hello");

  INF("Response: %s", sout.str().c_str());

  DBG("[Lesson 13]: Client 3 END");
  return 0;
}

