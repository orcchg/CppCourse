#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see Examples: https://github.com/jpbarrette/curlpp/tree/master/examples

const char* URL = "http://jsonplaceholder.typicode.com/posts";

struct Post {
  int id;
  int user_id;
  std::string title;
  std::string body;
};

Post createPost();
std::string convertToJson(const Post& post);
void upload(const std::string& body);

std::ostream& operator << (std::ostream& out, const Post& post) {
  out << "Post {\n\tid=" << post.id
      << "\n\tuser_id=" << post.user_id
      << "\n\ttitle=" << post.title
      << "\n\tbody=" << post.body
      << "\n}";
  return out;
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 4");

  // POST - create a new Post
  Post post = createPost();
  std::string request_body = convertToJson(post);
  upload(request_body);

  DBG("[Lesson 13]: Http 4 END");
  return 0;
}

Post createPost() {
  Post post;
  post.id = 1;  // will be ignored on Server
  post.user_id = 1;
  post.title = "New post";
  post.body = "This is a new post body to test create method via POST request";
  return post;
}

/**
 * @see http://jsonplaceholder.typicode.com/posts/1
 *
 *  {
 *    "userId": 1,
 *    "id": 1,
 *    "title": "Lorem Ipsum",
 *    "body": "quia et suscipit suscipit recusandae consequuntur"
 *  }
 *
 */
std::string convertToJson(const Post& post) {  // Quiz: write unit-test to check correctness
  std::ostringstream oss;
  oss << "{\n"
      << "\"userId\": " << post.user_id << ","
      << "\"id\": " << post.id << ","
      << "\"title\": \"" << post.title << "\","
      << "\"body\": \"" << post.body << "\""
      << "\n}";
  return oss.str();
}

void upload(const std::string& body) {
  curlpp::Easy request;
    
  request.setOpt(new curlpp::options::Url(URL)); 
  request.setOpt(new curlpp::options::Verbose(true)); 
    
  std::list<std::string> header; 
  header.push_back("Content-Type: application/json"); 
    
  request.setOpt(new curlpp::options::HttpHeader(header)); 
  request.setOpt(new curlpp::options::PostFields(body.c_str()));
  request.setOpt(new curlpp::options::PostFieldSize(body.size()));
    
  request.perform(); 
}

