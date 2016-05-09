#include <algorithm>
#include <fstream>
#include <iostream>
#include <functional>  // plus
#include <numeric>  // accumulate
#include <cmath>
#include <string>
#include <vector>
#include "logger.h"

long long hash(const std::string& str) {
  // Java String hash code: s[0]*7^(n-1) + s[1]*7^(n-2) + ... + s[n-1]
  int prime = 7;
  long long hash = 0;
  int power = str.length() - 1;

  for (auto it = str.begin(); it != str.end(); ++it, --power) {
    hash += static_cast<long long>(*it) * std::pow(prime, power);
  }
  return hash;
}

int main(int argc, char** argv) {
  DBG("[Lesson 4]: Algorithms 8");

  std::fstream fin;
  fin.open("lorem.txt", std::fstream::in);  // Quiz: replace 1st 'Lorem' to 'Lore' and see the difference

  std::vector<long long> hash_codes;
  std::string word;

  while (fin >> word) {
    auto value = hash(word);
    DBG("%s [%lli]", word.c_str(), value);
    hash_codes.push_back(value);
  }

  auto max_it = std::max_element(hash_codes.begin(), hash_codes.end());
  auto min_it = std::min_element(hash_codes.begin(), hash_codes.end());

  INF("Max hash: %lli, Min hash: %lli", *max_it, *min_it);

  fin.close();

  DBG("[Lesson 4]: Algorithms 8 [END]");
  return 0;
}

