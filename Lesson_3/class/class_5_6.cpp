#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include "logger.h"

struct Node {
  int key;
  char* value;
  
  Node(int k, const std::string& v);
  ~Node();
};

Node::Node(int k, const std::string& v)
  : key(k) {
  , value(new char[v.size()]) {
  INF("Constructor");
  strcpy(value, v.c_str());
}

Node::~Node() {
  WRN("~Destructor");
  if (value != nullptr) {
    delete [] value;
  }
  value = nullptr;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 5.6");
  
  int key;
  std::string value;
  
  std::cin >> key >> value;
  
  {  // block 1
    Node node(key, value);
  }  // end block 1
  
  DBG("[Lesson 3]: Class 5.6 [END]");
  return 0;
}
