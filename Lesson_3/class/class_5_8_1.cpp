#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include "logger.h"

class Node {
private:
  int key;
  char* value;
  
public:
  Node(int k, const std::string& v);
  Node(const Node& obj);
  ~Node();
  
  int getKey() const;
  char* getValue() const;
};

Node::Node(int k, const std::string& v)
  : key(k)
  , value(new char[v.size()]) {
  INF("Constructor");
  strcpy(value, v.c_str());
}

Node::Node(const Node& obj)
  : key(obj.key)
  , value(new char[strlen(obj.value)]) {
  CRT("Copy contructor");
  strcpy(value, obj.value);
}

Node::~Node() {
  WRN("~Destructor");
  if (value != nullptr) {
    delete [] value;
  }
  value = nullptr;
}

int Node::getKey() const {
  return key;
}

char* Node::getValue() const {
  return value;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.getKey() << ", " << node.getValue() << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 5.8.1");
  
  {  // block 1
    std::vector<Node> nodes = {Node(0, "Lesson"), Node(1, "three"), Node(2, "is"), Node(3, "devoted"), Node(4, "to"), Node(5, "classes")};
    for (auto& node : nodes) {
      std::cout << node << std::endl;
    }
  }  // end block 1
  
  DBG("[Lesson 3]: Class 5.8.1 [END]");
  return 0;
}

