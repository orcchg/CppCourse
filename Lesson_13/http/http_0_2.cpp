#include <iostream>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see http://www.curlpp.org/
/// @documentation: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
/// @see http://thecatapi.com/docs.html

int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 0.2");
  std::cout << curlpp::options::Url("http://thecatapi.com/api/images/get?format=xml&results_per_page=5");
  DBG("[Lesson 13]: Http 0.2 END");
  return 0;
}

