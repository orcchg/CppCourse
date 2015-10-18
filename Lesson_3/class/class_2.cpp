#include <string>
#include <iostream>
#include "logger.h"

struct Node {
  int key;
  std::string value;
  
  Node(int k, const std::string& v);
};

Node::Node(int k, const std::string& v) {
  key = k;
  value = v;
}

// Quiz: why there is no operator >> ?

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 2");
  
  int key;
  std::string value;
  std::cin >> key >> value;
  
  Node node(key, value);
  std::cout << "Node is: " << node << std::endl;
  
  DBG("[Lesson 3]: Class 2 [END]");
  return 0;
}
