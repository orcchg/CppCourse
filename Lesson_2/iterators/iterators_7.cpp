#include <iostream>
#include <cstdio>
#include "logger.h"

struct Node {  // Quiz: initialize Node instance from stdin and print into stdout
  int key;
  std::string value;

  void init(int key, const std::string& value);
};

void Node::init(int k, const std::string& v) {
  key = k;
  value = v;
}

/* Array */
// ----------------------------------------------------------------------------
template <typename T>
struct Array {
  typedef T* iterator;

  size_t size;
  T* data;

  void init(T* array, size_t size);

  iterator begin();
  iterator end();
};

template <typename T>
void Array<T>::init(T* array, size_t sz) {
  size = sz;
  data = array;
}

/* Iterator member-functions */
// ----------------------------------------------
template <typename T>
typename Array<T>::iterator Array<T>::begin() {
  return data;
}

template <typename T>
typename Array<T>::iterator Array<T>::end() {
  return data + size;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: Iterators 7");

  Node node_1, node_2, node_3, node_4, node_5;
  node_1.init(0, "Lesson");
  node_2.init(1, "two");
  node_3.init(2, "iterators");
  node_4.init(3, "template");
  node_5.init(4, "array");

  Node node_values[] = {node_1, node_2, node_3, node_4, node_5};
  size_t node_size = sizeof(node_values) / sizeof(Node);

  Array<Node> node_array;
  node_array.init(node_values, node_size);
  for (typename Array<Node>::iterator it = node_array.begin(); it != node_array.end(); ++it) {
    std::cout << "{" << it->key << ", " << it->value << "} ";
  }
  printf("\n");

  DBG("[Lesson 2]: Iterators 7 [END]");
}

