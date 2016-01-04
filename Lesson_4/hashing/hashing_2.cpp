#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include "logger.h"

struct Hasher {
  size_t operator()(const std::string& str) const;
};

size_t Hasher::operator()(const std::string& str) const {
  // Java String hash code: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
  int prime = 31;
  size_t hash = 0;
  int power = str.length() - 1;

  for (auto it = str.begin(); it != str.end(); ++it, --power) {
    hash += static_cast<size_t>(*it) * std::pow(prime, power);
  }
  return hash;
}

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Hashing 2");

  std::unordered_set<std::string, Hasher> hash_set = {"Lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing", "elit"};

  std::copy(hash_set.begin(), hash_set.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Hashing 2 [END]");
  return 0;
}

