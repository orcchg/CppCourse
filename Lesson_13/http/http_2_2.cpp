#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdio>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

/// @see Json Parser: https://github.com/miloyip/rapidjson
/// @see Documentation: http://rapidjson.org/md_doc_tutorial.html
/// @see Example: https://github.com/miloyip/rapidjson/blob/master/example/tutorial/tutorial.cpp
/// @see http://jsonplaceholder.typicode.com/

const char* URL_JSON_FAKE_SERVER = "http://jsonplaceholder.typicode.com/posts";

struct Post {
  int id;
  int user_id;
  std::string title;
  std::string body;
};

void processJsonString(const std::string& json, std::vector<Post>* posts);
Post processRawPost(const rapidjson::Value& raw_post);

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
  DBG("[Lesson 13]: Http 2.2");

  std::ostringstream sout;
  sout << curlpp::options::Url(URL_JSON_FAKE_SERVER);

  std::vector<Post> posts;
  processJsonString(sout.str(), &posts);
  std::copy(posts.begin(), posts.end(), std::ostream_iterator<Post>(std::cout, "\n"));

  DBG("[Lesson 13]: Http 2.2 END");
  return 0;
}

/* Process Json document */
// ------------------------------------------------------------------------------------------------
void processJsonString(const std::string& json, std::vector<Post>* posts) {
  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.IsArray()) {  // json could also be an Object
    int size = document.Size();
    INF("Found an Array of size: %i", size);
    for (int i = 0; i < size; ++i) {
      const rapidjson::Value& raw_post = document[i];
      Post post = processRawPost(raw_post);
      posts->push_back(post);
    }
  } else {
    ERR("Invalid json: not an array");
  }
}

Post processRawPost(const rapidjson::Value& raw_post) {
  const char* ITEM_ID = "id";
  const char* ITEM_USER_ID = "userId";
  const char* ITEM_TITLE = "title";
  const char* ITEM_BODY = "body";

  Post post;

  if (raw_post.IsObject()) {  // could also be an Array
    assert("No item: id" && raw_post.HasMember(ITEM_ID));
    assert("Not an integer: id" && raw_post[ITEM_ID].IsInt());
    post.id = raw_post[ITEM_ID].GetInt();

    assert("No item: user_id" && raw_post.HasMember(ITEM_USER_ID));
    assert("Not an integer: user_id" && raw_post[ITEM_USER_ID].IsInt());
    post.user_id = raw_post[ITEM_USER_ID].GetInt();

    assert("No item: title" && raw_post.HasMember(ITEM_TITLE));
    assert("Not a string: title" && raw_post[ITEM_TITLE].IsString());
    post.title = std::string(raw_post[ITEM_TITLE].GetString());

    assert("No item: body" && raw_post.HasMember(ITEM_BODY));
    assert("Not a string: body" && raw_post[ITEM_BODY].IsString());
    post.body = std::string(raw_post[ITEM_BODY].GetString());
  } else {
    ERR("Invalid json object");
  }

  return post;
}

