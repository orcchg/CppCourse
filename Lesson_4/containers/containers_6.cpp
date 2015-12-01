#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <set>
#include "logger.h"

struct Node {
  int key;
  std::string value;

  Node(int key, const std::string& value);
  bool operator < (const Node& node) const;
  bool operator == (const Node& node) const;
  bool operator != (const Node& node) const;
};

Node::Node(int key, const std::string& value)
  : key(key), value(value) {
}

bool Node::operator < (const Node& node) const {
  return key < node.key;
}

bool Node::operator == (const Node& node) const {
  return key == node.key;
}

bool Node::operator != (const Node& node) const {
  return !(*this == node);
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Containers 6");

  std::set<int> int_set = {5, 7, 2, 5, 9, -4, 0, -2, -1, 3, 8, 9, 2, 5, 0, 1, 0, 0, 5, 5, 5, 5};
  std::copy(int_set.begin(), int_set.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::set<double> real_set = {3.14, 2.71, 0.05, -2.88, 0.1, -5.72, 0.137, -9.8, 22.4, 8.31, 0.2};
  std::copy(real_set.begin(), real_set.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;

  std::set<std::string> str_set = {"Lorem", "ipsum", "dolor", "ipsum", "la", "derecha", "y", "la", "Lorem"};
  std::copy(str_set.begin(), str_set.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;

  std::set<Node> node_set = {Node(0, "zero"), Node(0, "zero"), Node(2, "two"), Node(2, "two"), Node(2, "two"), Node(5, "five")};
  std::copy(node_set.begin(), node_set.end(), std::ostream_iterator<Node>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Containers 6 [END]");
  return 0;
}

