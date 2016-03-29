#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see Examples: https://github.com/jpbarrette/curlpp/tree/master/examples
/// @see cURL Options: https://curl.haxx.se/libcurl/c/curl_easy_setopt.html

const char* URL = "http://jsonplaceholder.typicode.com/posts/1";

void deletePost();

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 4.2");

  // DELETE - delete Post
  deletePost();

  DBG("[Lesson 13]: Http 4.2 END");
  return 0;
}

/// @see https://curl.haxx.se/libcurl/c/curl_easy_setopt.html - there is no DELETE option
/// @see Solution - use custom option:
///      http://www.codeproject.com/Questions/490432/usepluslibcurlplustoplussendplushttpplusdeleteplus
void deletePost() {
  curlpp::Easy request;
    
  request.setOpt(new curlpp::options::Url(URL)); 
  request.setOpt(new curlpp::options::Verbose(true)); 
    
  std::list<std::string> header; 
  header.push_back("Content-Type: application/json"); 
    
  request.setOpt(new curlpp::options::HttpHeader(header)); 
  request.setOpt(new curlpp::options::CustomRequest("DELETE"));
    
  request.perform(); 
}

