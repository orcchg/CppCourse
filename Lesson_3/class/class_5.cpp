#include <string>
#include <iostream>
#include "logger.h"

struct Node {
  int key;
  std::string value;
  
  Node(int k, const std::string& v);
};

Node::Node(int k, const std::string& v)
  : key(k)
  , value(v) {
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 5");
  
  int key;
  std::string value;
  std::cin >> key >> value;
  
  Node* node = new Node(key, value);
  
  std::cout << "Node is: " << *node << std::endl;
  
  delete node;
  node = nullptr;
  
  DBG("[Lesson 3]: Class 5 [END]");
  return 0;
}
