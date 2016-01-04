#include <algorithm>
#include <iostream>
#include <iterator>  // back_inserter
#include <cmath>
#include <string>
#include <vector>
#include "logger.h"

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

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 1");

  std::vector<std::string> words = {"Lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing", "elit"};
  std::vector<long> hash_codes;

  std::transform(words.begin(), words.end(), std::back_inserter(hash_codes), hash);
  std::copy(hash_codes.begin(), hash_codes.end(), std::ostream_iterator<long>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Algorithms 1 [END]");
  return 0;
}

