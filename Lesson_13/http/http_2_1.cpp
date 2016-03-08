#include <iostream>
#include <sstream>
#include <string>
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

const char* URL_JSON_FAKE_SERVER = "http://jsonplaceholder.typicode.com/posts/1";

struct Post {
  int id;
  int user_id;
  std::string title;
  std::string body;
};

Post processJsonString(const std::string& json);

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
  DBG("[Lesson 13]: Http 2.1");

  std::ostringstream sout;
  sout << curlpp::options::Url(URL_JSON_FAKE_SERVER);

  Post post = processJsonString(sout.str());
  std::cout << post << std::endl;

  DBG("[Lesson 13]: Http 2.1 END");
  return 0;
}

/* Process Json document */
// ------------------------------------------------------------------------------------------------
Post processJsonString(const std::string& json) {
  const char* ITEM_ID = "id";
  const char* ITEM_USER_ID = "userId";
  const char* ITEM_TITLE = "title";
  const char* ITEM_BODY = "body";

  Post post;

  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.IsObject()) {  // json could also be an Array
    assert("No item: id" && document.HasMember(ITEM_ID));
    assert("Not an integer: id" && document[ITEM_ID].IsInt());
    post.id = document[ITEM_ID].GetInt();

    assert("No item: user_id" && document.HasMember(ITEM_USER_ID));
    assert("Not an integer: user_id" && document[ITEM_USER_ID].IsInt());
    post.user_id = document[ITEM_USER_ID].GetInt();

    assert("No item: title" && document.HasMember(ITEM_TITLE));
    assert("Not a string: title" && document[ITEM_TITLE].IsString());
    post.title = std::string(document[ITEM_TITLE].GetString());

    assert("No item: body" && document.HasMember(ITEM_BODY));
    assert("Not a string: body" && document[ITEM_BODY].IsString());
    post.body = std::string(document[ITEM_BODY].GetString());
  } else {
    ERR("Invalid json: %s", json.c_str());
  }

  return post;
}

