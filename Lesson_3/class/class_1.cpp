#include <string>
#include <iostream>
#include "logger.h"

struct Node {
  int key;
  std::string value;
  
  void init(int k, const std::string& v);
};

void Node::init(int k, const std::string& v) {
  key = k;
  value = v;
}

std::istream* operator >> (std::istream& in, Node& node) {
  int key;
  std::string value;
  
  in >> key >> value;
  node.init(key, value);
  
  return in;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 1");
  
  Node node;
  std::cin >> node;
  std::cout << "Node is: " << node << std::endl;
  
  DBG("[Lesson 3]: Class 1 [END]");
  return 0;
}
