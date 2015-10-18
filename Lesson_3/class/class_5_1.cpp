#include <string>
#include <iostream>
#include <vector>
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
  DBG("[Lesson 3]: Class 5.1");
  
  std::vector<Node> nodes = {Node(0, "Lesson"), Node(1, "three"), Node(2, "is"), Node(3, "devoted"), Node(4, "to"), Node(5, "classes")};
  // Quiz: write vector's content into stdout
  
  DBG("[Lesson 3]: Class 5.1 [END]");
  return 0;
}
