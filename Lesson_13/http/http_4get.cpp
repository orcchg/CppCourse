#include <iostream>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see http://www.curlpp.org/
/// @see Documentation: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
/// @see Examples: https://github.com/jpbarrette/curlpp/tree/master/examples

int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 4get");
  //std::cout << curlpp::options::Url("http://127.0.0.1:9000/customers/?limit=10&offset=7");
  //std::cout << curlpp::options::Url("http://127.0.0.1:9000/address/?address_id=7");
  std::cout << curlpp::options::Url("http://127.0.0.1:9000/customers/?limit=10&offset=598");
  DBG("[Lesson 13]: Http 4get END");
  return 0;
}

