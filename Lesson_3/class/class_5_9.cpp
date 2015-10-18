#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include "logger.h"

class Node {
  int key;
  size_t size;
  char* value;
  
public:
  Node(int k, const std::string& v);
  ~Node();
  
  int getKey();
  char* getValue();
};

Node::Node(int k, const std::string& v)  // Quiz: order of initialization
  : key(k) {
  , size(v.size())
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

int Node::getKey() {
  return key;
}

char* getValue() {
  return value;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.getKey() << ", ";
  for (size_t i = 0; i < size; ++i) {
    out << getValue()[i];
  }
  out << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 5.9");
  
  {  // block 1
    std::vector<Node> nodes = {Node(0, "Lesson"), Node(1, "three"), Node(2, "is"), Node(3, "devoted"), Node(4, "to"), Node(5, "classes")};
    for (auto& node : nodes) {
	  std::cout << node << std::endl;
	}
  }  // end block 1
  
  DBG("[Lesson 3]: Class 5.9 [END]");
  return 0;
}
