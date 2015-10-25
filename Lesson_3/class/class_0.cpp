#include <string>
#include <iostream>
#include "logger.h"

struct Node {
  int key;
  std::string value;
};

std::istream& operator >> (std::istream& in, Node& node) {
  in >> node.key >> node.value;
  return in;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 0");
  
  Node node;
  std::cin >> node;
  std::cout << "Node is: " << node << std::endl;
  
  DBG("[Lesson 3]: Class 0 [END]");
  return 0;
}

