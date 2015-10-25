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
  : key(k)
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
  DBG("[Lesson 3]: Class 5.7");
  
  {  // block 1
    std::vector<Node> nodes = {Node(0, "Lesson"), Node(1, "three"), Node(2, "is"), Node(3, "devoted"), Node(4, "to"), Node(5, "classes")};
    DBG("Vector filled");
    for (auto& node : nodes) {
      std::cout << node << std::endl;
    }
  }  // end block 1
  
  DBG("[Lesson 3]: Class 5.7 [END]");
  return 0;
}
