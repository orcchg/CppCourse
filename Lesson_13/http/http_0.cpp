#include <iostream>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see http://www.curlpp.org/
/// @see Documentation: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
/// @see Examples: https://github.com/jpbarrette/curlpp/tree/master/examples

int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 0");
  std::cout << curlpp::options::Url("http://example.com");
  DBG("[Lesson 13]: Http 0 END");
  return 0;
}

