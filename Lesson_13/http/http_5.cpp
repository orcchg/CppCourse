#include <iostream>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see http://www.curlpp.org/
/// @documentation: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
/// @see http://thecatapi.com/docs.html

int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 5");
  std::cout << curlpp::options::Url("http://example.com");
  DBG("[Lesson 13]: Http 5 END");
  return 0;
}

