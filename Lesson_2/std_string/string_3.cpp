#include <iostream>
#include <string>
#include "include/logger.h"

int main(int argc, char** argv) {
  DBG("[Lesson 2]: STD string 3");

  // Length
  std::string str = "Hello, World";
  std::cout << "Length: " << str.length() << std::endl;

  // Get char at position
  int position = 0;
  std::cout << "Enter position: ";
  std::cin >> position;
  std::cout << "char at [" << position << "]: " << str[position] << std::endl;

  // Append char
  str.push_back('!');
  std::cout << str << std::endl;

  // Check for empty
  std::cout << "Is empty: " << str.empty() << std::endl;
  str.clear();
  std::cout << "Is empty: " << str.empty() << std::endl;

  // Find substring
  str.assign("Hello, World!");
  std::string hello = "Hello";
  std::string small = "Small";

  size_t index = str.find(hello);
  str.replace(index, hello.size(), small);
  std::cout << str << std::endl;

  // Get substring
  std::string world = str.substr(7);
  std::cout << world << std::endl;

  // Cat and compare
  std::cout << "Concatenation: " << hello + ", " + world << std::endl;
  std::cout << "Compare " << hello << " and " << world << ": " << hello.compare(world) << std::endl;

  // Find any of character
  std::cout << "First occurence of any of 'lod': " << str.find_first_of("lod") << std::endl;
  
  // Trim whitespaces
  str = "   Some leading and trailing whitespaces   Yeah   ";
  std::string whitespaces(" \t\f\v\n\r");
  size_t found = str.find_last_not_of(whitespaces);
  if (found != std::string::npos) {
    str.erase(found + 1);
  } else {
    str.clear();  // str is all whitespace
  }
  std::cout << '[' << str << "]\n";

  DBG("[Lesson 2]: STD string 3 [END]");
  return 0;
}

