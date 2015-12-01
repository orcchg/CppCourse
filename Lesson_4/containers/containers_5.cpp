#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include "logger.h"

struct Node {
  int key;
  std::string value;

  Node();  // std::array requires default ctor
  Node(int key, const std::string& value);
};

Node::Node()
  : key(0), value("zero") {
}

Node::Node(int key, const std::string& value)
  : key(key), value(value) {
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Containers 5");

  std::array<int, 5> int_array;
  int_array.fill(10);
  std::copy(int_array.begin(), int_array.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::array<std::string, 5> str_array;
  str_array.fill("Lorem Ipsum");
  std::copy(str_array.begin(), str_array.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;

  std::array<Node, 5> node_array;
  for (size_t i = 0; i < node_array.size(); ++i) {
    node_array[i] = Node(i, "Lorem Ipsum");
  }
  std::copy(node_array.begin(), node_array.end(), std::ostream_iterator<Node>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Containers 5 [END]");
  return 0;
}

