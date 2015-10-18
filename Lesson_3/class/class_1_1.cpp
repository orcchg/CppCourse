#include <string>
#include <iostream>
#include <cstdlib>
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

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 1.1");
  
  int key;
  std::string value;
  std::cin >> key >> value;
  
  Node* node = (Node*) malloc(sizeof(Node));
  node->init(key, value);
  
  std::cout << "Node is: " << *node << std::endl;
  
  free(node);
  node = nullptr;
  
  DBG("[Lesson 3]: Class 1.1 [END]");
  return 0;
}
