#include <iostream>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see http://www.curlpp.org/
/// @documentation: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf

int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 0.1");

  curlpp::options::Url url(std::string("http://example.com"));
  curlpp::Easy request;
  request.setOpt(url);

  request.perform();  // do request and print the response into STDOUT

  DBG("[Lesson 13]: Http 0.1 END");
  return 0;
}

