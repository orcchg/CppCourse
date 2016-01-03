#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "logger.h"

struct Node {
  int key;
  std::string value;

  Node();
  Node(int key, const std::string& value);
  bool operator < (const Node& node) const;
  bool operator == (const Node& node) const;
  bool operator != (const Node& node) const;
};

Node::Node()
  : key(0), value("") {
}

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
  out << "\e[5;01;33m{\e[m" << node.key << ", " << node.value << "\e[5;01;33m}\e[m";
  return out;
}

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::pair<Key, Value>& p) {
  out << "[" << p.first << ", " << p.second << "]";
  return out;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Containers 7");

  std::map<int, int> int_map;
  int_map[0] = 0;
  int_map[1] = 1;
  int_map[2] = 2;
  int_map[3] = 3;
  int_map[4] = 4;
  for (auto& item : int_map) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  std::map<int, double> real_map;
  real_map[0] = 3.14;
  real_map[1] = 2.71;
  real_map[2] = 0.05;
  real_map[3] = -2.88;
  real_map[4] = 0.1;
  for (auto& item : real_map) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  std::map<int, std::string> str_map;
  str_map[0] = "Lorem";
  str_map[1] = "ipsum";
  str_map[2] = "dolor";
  str_map[3] = "ipsum";
  str_map[4] = "la";
  for (auto& item : str_map) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  std::map<int, Node> node_map;
  node_map[0] = Node(0, "zero");
  node_map[1] = Node(1, "one");
  node_map[2] = Node(2, "two");
  node_map[3] = Node(3, "three");
  node_map[4] = Node(4, "four");
  for (auto& item : node_map) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  DBG("[Lesson 4]: Containers 7 [END]");
  return 0;
}

