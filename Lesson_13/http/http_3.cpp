#include <iostream>
#include <fstream>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see http://www.curlpp.org/
/// @documentation: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
/// @see http://thecatapi.com/docs.html
/// @see XML parser: http://stackoverflow.com/questions/9387610/what-xml-parser-should-i-use-in-c

const char* URL_CATAPI = "http://thecatapi.com/api/images/get?format=xml&results_per_page=5";

int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 3");
  //
  DBG("[Lesson 13]: Http 3 END");
  return 0;
}

