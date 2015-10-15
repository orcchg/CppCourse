#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "logger.h"

/* Structure */
// ----------------------------------------------------------------------------
struct Node {
  int key;
  std::string value;

  void init(int key, const std::string& value);
};

void Node::init(int k, const std::string& v) {
  key = k;
  value = v;
}

/* Input & Output streaming */
// ----------------------------------------------
std::istream& operator >> (std::istream& in, Node& node) {
  in >> node.key >> node.value;
  return in;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 15");

  Node node;

  std::cout << "Введите пару (число, строка): ";
  std::cin >> node;
  std::cout << std::endl;

  std::cout << "Структура: " << node << " выведена в stdout" << std::endl;

  DBG("[Lesson 2]: IO 15 [END]");
  return 0;
}

