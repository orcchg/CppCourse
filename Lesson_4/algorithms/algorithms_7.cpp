#include <algorithm>
#include <fstream>
#include <iostream>
#include <functional>  // plus
#include <numeric>  // accumulate
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
  DBG("[Lesson 4]: Algorithms 7");

  std::fstream fin;
  fin.open("lorem.txt", std::fstream::in);  // Quiz: replace 1st 'Lorem' to 'Lore' and see the difference

  std::vector<long> hash_codes;
  std::string word;

  while (fin >> word) {
    hash_codes.push_back(hash(word));
  }

  int sum = std::accumulate(hash_codes.begin(), hash_codes.end(), 0, std::plus<int>());
  std::cout << "Total words: " << hash_codes.size() << ", Control Sum: " << sum << std::endl;

  fin.close();

  DBG("[Lesson 4]: Algorithms 7 [END]");
  return 0;
}

