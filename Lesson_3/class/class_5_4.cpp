#include <string>
#include <iostream>
#include <vector>
#include "logger.h"

struct Node {
  int key;
  char* value;
  
  Node(int k, const std::string& v);
  void destroy();
};

Node::Node(int k, const std::string& v)
  : key(k)
  , value(new char[v.size()]) {
  for (size_t i = 0; i < v.size(); ++i) {
    value[i] = v[i];
  }
}

void Node::destroy() {
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
  DBG("[Lesson 3]: Class 5.4");
  
  {  // block 1
    std::vector<Node> nodes = {Node(0, "Lesson"), Node(1, "three"), Node(2, "is"), Node(3, "devoted"), Node(4, "to"), Node(5, "classes")};
    for (auto& node : nodes) {
      std::cout << node << std::endl;
      node.destroy();  // clear
    }
  }  // end block 1
  
  DBG("[Lesson 3]: Class 5.4 [END]");
  return 0;
}
