#include <algorithm>
#include <iostream>
#include <iterator>  // back_inserter
#include <cmath>
#include <string>
#include <vector>
#include "logger.h"

struct Node {
  long key;
  std::string value;
};

long hash(const std::string& str) {
  // Java String hash code: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
  int prime = 31;
  long hash = 0;
  int power = str.length() - 1;

  for (auto it = str.begin(); it != str.end(); ++it, --power) {
    hash += static_cast<long>(*it) * std::pow(prime, power);
  }
  return hash;
}

Node makeNode(const std::string str) {
  Node node;
  node.key = hash(str);
  node.value = str;
  return node;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 2");

  std::vector<std::string> words = {"Lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing", "elit"};
  std::vector<Node> nodes;

  std::transform(words.begin(), words.end(), std::back_inserter(nodes), makeNode);
  std::copy(nodes.begin(), nodes.end(), std::ostream_iterator<Node>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Algorithms 2 [END]");
  return 0;
}

