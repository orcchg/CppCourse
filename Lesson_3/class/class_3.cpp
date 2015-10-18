#include <string>
#include <iostream>
#include <cstdlib>
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

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 3");
  
  int key;
  std::string value;
  std::cin >> key >> value;
  
  Node* node = (Node*) malloc(sizeof(Node));
  node->key = key;
  node->value = value;
  
  std::cout << "Node is: " << *node << std::endl;
  
  free(node);
  node = nullptr;
  
  DBG("[Lesson 3]: Class 3 [END]");
  return 0;
}
