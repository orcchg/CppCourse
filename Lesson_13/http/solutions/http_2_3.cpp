#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>
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
  DBG("[Lesson 13]: Http 2.3");

  std::ostringstream sout;
  sout << curlpp::options::Url(URL_JSON_FAKE_SERVER);

  std::vector<Post> posts;
  processJsonString(sout.str(), &posts);
  std::copy(posts.begin(), posts.end(), std::ostream_iterator<Post>(std::cout, "\n"));

  DBG("[Lesson 13]: Http 2.3 END");
  return 0;
}

/* Process Json document */
// ------------------------------------------------------------------------------------------------
void processJsonString(const std::string& json, std::vector<Post>* posts) {
  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.IsArray()) {  // json could also be an Object
    INF("Found an Array of size: %i", document.Size());
    for (rapidjson::Value::ConstValueIterator it = document.Begin(); it != document.End(); ++it) {
      Post post = processRawPost(*it);
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
    for (rapidjson::Value::ConstMemberIterator it = raw_post.MemberBegin(); it != raw_post.MemberEnd(); ++it) {
      const char* name = it->name.GetString();
      if (it->value.GetType() == rapidjson::Type::kNumberType) {  // 6 is Number
        int value = it->value.GetInt();
        if (strcmp(name, ITEM_ID) == 0) {
          post.id = value;
        } else if (strcmp(name, ITEM_USER_ID) == 0) {
          post.user_id = value;
        }
      } else if (it->value.GetType() == rapidjson::Type::kStringType) {  // 5 is String
        const char* value = it->value.GetString();
        if (strcmp(name, ITEM_TITLE) == 0) {
          post.title = std::string(value);
        } else if (strcmp(name, ITEM_BODY) == 0) {
          post.body = std::string(value);
        }
      }
    }
  } else {
    ERR("Invalid json object");
  }

  return post;
}

