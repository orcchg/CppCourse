#include <string>
#include <iostream>
#include <vector>
#include "logger.h"

struct Node {
  int key;
  char* value;
  
  Node(int k, const std::string& v);
};

Node::Node(int k, const std::string& v)  // Quiz: use initializer list for 'value' data-member
  : key(k) {
  value = new char[v.size()];
  for (size_t i = 0; i < v.size(); ++i) {
    value[i] = v[i];
  }
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 5.2");
  
  {  // block 1
    std::vector<Node> nodes = {Node(0, "Lesson"), Node(1, "three"), Node(2, "is"), Node(3, "devoted"), Node(4, "to"), Node(5, "classes")};
    for (auto& node : nodes) {
	  std::cout << node << std::endl;
	}
  }  // end block 1  (memory leak)
  
  DBG("[Lesson 3]: Class 5.2 [END]");
  return 0;
}
