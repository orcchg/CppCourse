#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include "logger.h"

template <typename T>
void print(T array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

/* Node */
// ------------------------------------------------------------------------------------------------
struct Node {
  int key;
  std::string value;

  Node(int key, const std::string& value);

  bool operator < (const Node& rhs) const;
};

Node::Node(int key, const std::string& value)
  : key(key)
  , value(value) {
}

bool Node::operator < (const Node& rhs) const {
  return key < rhs.key;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
}

/* Template specialization */
// ------------------------------------------------------------------------------------------------
namespace std {

template <>
struct greater<Node> {
  bool operator() (const Node& x, const Node& y) const {
    return x.key > y.key;
  }
};

}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Templates 0.2");

  int int_array[10] = {5, 8, 1, 12, -4, -7, 3, 5, 9, 0};
  INF("Sorting <int>");
  print(int_array, 10);
  std::sort(int_array, int_array + 10, std::greater<int>());
  print(int_array, 10);

  double double_array[10] = {5.31, 8.11, 1.09, 12.21, -4.05, -7.57, 3.48, 5.02, 9.09, 0.1};
  INF("Sorting <double>");
  print(double_array, 10);
  std::sort(double_array, double_array + 10, std::greater<double>());
  print(double_array, 10);

  Node node_array[10] = {
    Node(5, "five"), Node(8, "eight"),
    Node(1, "one"), Node(12, "twelve"), Node(-4, "-four"), Node(-7, "-seven"),
    Node(3, "three"), Node(5, "five"), Node(9, "nine"), Node(0, "zero")};
  INF("Sorting <Node>");
  print(node_array, 10);
  std::sort(node_array, node_array + 10, std::greater<Node>());
  print(node_array, 10);

  DBG("[Lesson 4]: Templates 0.2 [END]");
  return 0;
}

