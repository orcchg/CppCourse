#include <iostream>
#include <fstream>
#include <string>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see Json Parser: https://github.com/miloyip/rapidjson
/// @see http://jsonplaceholder.typicode.com/

const char* URL_JSON_FAKE_SERVER = "http://jsonplaceholder.typicode.com/posts";

const char* FILENAME_JSON = "posts_response.json";

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 2");

  std::fstream fout;
  fout.open(FILENAME_JSON, std::fstream::out);
  fout << curlpp::options::Url(URL_JSON_FAKE_SERVER);
  fout.close();

  DBG("[Lesson 13]: Http 2 END");
  return 0;
}

