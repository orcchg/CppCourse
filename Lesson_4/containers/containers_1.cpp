#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include "logger.h"

struct Node {
  int key;
  std::string value;

  Node(int key, const std::string& value);
};

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
  DBG("[Lesson 4]: Containers 1");

  std::vector<int> int_vector = {5, 7, 2, 12, 9, -4, 0, -2, -1, 3, 8, 9, 2, 3, 0, 1, 6, 11, -15, 14, 19, 21};
  std::copy(int_vector.begin(), int_vector.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<double> real_vector = {3.14, 2.71, 0.05, -2.88, 0.1, -5.72, 0.137, -9.8, 22.4, 8.31, 0.2};
  std::copy(real_vector.begin(), real_vector.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;

  std::vector<std::string> str_vector = {"Lorem", "ipsum", "dolor", "tut", "la", "derecha", "y", "ala", "izquerda", "vasilala", "por", "mano"};
  std::copy(str_vector.begin(), str_vector.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;

  std::vector<Node> node_vector = {Node(0, "zero"), Node(1, "one"), Node(2, "two"), Node(3, "three"), Node(4, "four"), Node(5, "five")};
  std::copy(node_vector.begin(), node_vector.end(), std::ostream_iterator<Node>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Containers 1 [END]");
  return 0;
}

