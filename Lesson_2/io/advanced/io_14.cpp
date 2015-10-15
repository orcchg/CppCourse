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

/* Output streaming */
// ----------------------------------------------
std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 2]: IO 14");

  int key = 0;
  std::string value = "";

  std::cout << "Введите пару (число, строка): ";
  std::cin >> key >> value;
  std::cout << std::endl;

  Node node;
  node.init(key, value);

  std::cout << "Структура: " << node << " выведена в stdout" << std::endl;

  DBG("[Lesson 2]: IO 14 [END]");
  return 0;
}

