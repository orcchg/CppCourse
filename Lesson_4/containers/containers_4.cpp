#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <deque>
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
  DBG("[Lesson 4]: Containers 4");

  std::deque<int> int_deque = {5, 7, 2, 12, 9, -4, 0, -2, -1, 3, 8, 9, 2, 3, 0, 1, 6, 11, -15, 14, 19, 21};
  std::copy(int_deque.begin(), int_deque.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::deque<double> real_deque = {3.14, 2.71, 0.05, -2.88, 0.1, -5.72, 0.137, -9.8, 22.4, 8.31, 0.2};
  std::copy(real_deque.begin(), real_deque.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;

  std::deque<std::string> str_deque = {"Lorem", "ipsum", "dolor", "tut", "la", "derecha", "y", "ala", "izquerda", "vasilala", "por", "mano"};
  std::copy(str_deque.begin(), str_deque.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;

  // Node deque
  std::deque<Node> node_deque;

  node_deque.push_back(Node(0, "zero"));
  node_deque.push_back(Node(1, "one"));
  node_deque.push_back(Node(2, "two"));

  node_deque.push_front(Node(3, "three"));
  node_deque.push_front(Node(4, "four"));
  node_deque.push_front(Node(5, "five"));

  std::copy(node_deque.begin(), node_deque.end(), std::ostream_iterator<Node>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Containers 4 [END]");
  return 0;
}

