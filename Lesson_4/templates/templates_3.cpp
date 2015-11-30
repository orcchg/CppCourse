#include <iostream>
#include <string>
#include "logger.h"

template <typename T>
bool greater(const T& lhs, const T& rhs) {
  return lhs > rhs;
}

namespace sort {

template <typename T>
void insertion(T array[], size_t size) {
  for (size_t j = 1; j < size; ++j) {
    T key = array[j];
    int i = j - 1;
    while (i >= 0 && greater(array[i], key)) {
      array[i + 1] = array[i];
      --i;
    }
    array[i + 1] = key;
  }
}

}

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
};

Node::Node(int key, const std::string& value)
  : key(key)
  , value(value) {
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
}

template <>
bool greater<Node>(const Node& lhs, const Node& rhs) {  // template specialization
  return lhs.key > rhs.key;
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Templates 3");

  int int_array[10] = {5, 8, 1, 12, -4, -7, 3, 5, 9, 0};
  INF("Sorting <int>");
  print(int_array, 10);
  sort::insertion(int_array, 10);
  print(int_array, 10);

  double double_array[10] = {5.31, 8.11, 1.09, 12.21, -4.05, -7.57, 3.48, 5.02, 9.09, 0.1};
  INF("Sorting <double>");
  print(double_array, 10);
  sort::insertion(double_array, 10);
  print(double_array, 10);

  Node node_array[10] = {
    Node(5, "five"), Node(8, "eight"),
    Node(1, "one"), Node(12, "twelve"), Node(-4, "-four"), Node(-7, "-seven"),
    Node(3, "three"), Node(5, "five"), Node(9, "nine"), Node(0, "zero")};
  INF("Sorting <Node>");
  print(node_array, 10);
  sort::insertion(node_array, 10);
  print(node_array, 10);

  DBG("[Lesson 4]: Templates 3 [END]");
  return 0;
}

