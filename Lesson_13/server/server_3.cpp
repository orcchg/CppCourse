#include "logger.h"

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
 * HTTP Server
 *
 * @see https://www.jmarshall.com/easy/http/
 *
 * HTTP is a stateless protocol - it not maintaining any connection information
 * between transactions. After delivering the response to an HTTP Client, the 
 * HTTP Server always closes an established connection.
 */

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 13]: Server 3");

  DBG("[Lesson 13]: Server 3 END");
  return 0;
}

