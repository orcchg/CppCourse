#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "bst.h"
#include "logger.h"

std::default_random_engine rng;

float truncate(float value, int precision) {
  int sign = value > 0 ? 1 : -1;
  unsigned int temp = (value * pow(10, precision)) * sign;
  return static_cast<float>(temp) / pow(10, precision) * sign;
}

// ----------------------------------------------------------------------------
template <typename T>
void fill(size_t size, BSTree<T>* bst);

template <>
void fill<int>(size_t size, BSTree<int>* bst) {
  INF("Inserting into BSTree...");
  for (size_t i = 0; i < size; ++i) {
    int value = rand() % 100;
    printf("\e[5;00;36m%i \e[m", value);
    bst->insert(value);
  }
  printf("\n");
}

template <>
void fill<float>(size_t size, BSTree<float>* bst) {
  std::uniform_real_distribution<float> distribution(0.0f, 1.01f);
  INF("Inserting into BSTree...");
  for (size_t i = 0; i < size; ++i) {
    float value = distribution(rng);
    value = truncate(value, 4);
    printf("\e[5;00;36m%.4f \e[m", value);
    bst->insert(value);
  }
  printf("\n");
}

template <>
void fill<std::string>(size_t size, BSTree<std::string>* bst) {
  INF("Inserting into BSTree...");
  for (size_t i = 0; i < size; ++i) {
    int length = rand() % 2 + 1;
    std::string value = "";
    for (size_t j = 0; j < length; ++j) {
      char ch = 'a' + rand() % 6;
      value.push_back(ch);
    }
    printf("\e[5;00;36m%s \e[m", value.c_str());
    bst->insert(value);
  }
  printf("\n");
}

// ----------------------------------------------------------------------------
template <typename T>
void remove(size_t size, BSTree<T>* bst);

template <>
void remove<int>(size_t size, BSTree<int>* bst) {
  WRN("Removing from BSTree...");
  for (size_t i = 0; i < size; ++i) {
    int value = rand() % 100;
    if (bst->contains(value)) {
      printf("\e[5;00;31m%i \e[m", value);
    } else {
      printf("%i ", value);
    }
    bst->remove(value);
  }
  printf("\n");
}

template <>
void remove<float>(size_t size, BSTree<float>* bst) {
  std::uniform_real_distribution<float> distribution(0.0f, 1.01f);
  WRN("Removing from BSTree...");
  for (size_t i = 0; i < size; ++i) {
    float value = distribution(rng);
    value = truncate(value, 4);
    if (bst->contains(value)) {
      printf("\e[5;00;31m%.4f \e[m", value);
    } else {
      printf("%.4lf ", value);
    }
    bst->remove(value);
  }
  printf("\n");
}

template <>
void remove<std::string>(size_t size, BSTree<std::string>* bst) {
  WRN("Removing from BSTree...");
  for (size_t i = 0; i < size; ++i) {
    int length = rand() % 2 + 1;
    std::string value = "";
    for (size_t j = 0; j < length; ++j) {
      char ch = 'a' + rand() % 6;
      value.push_back(ch);
    }
    if (bst->contains(value)) {
      printf("\e[5;00;31m%s \e[m", value.c_str());
    } else {
      printf("%s ", value.c_str());
    }
    bst->remove(value);
  }
  printf("\n");
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Class templates 1");

  // --------------------------------------------
  CRT("Integer BSTree");
  BSTree<int> int_tree;
  fill(20, &int_tree);
  int_tree.print();
  printf("\n");

  fill(5, &int_tree);
  int_tree.print();
  printf("\n");

  remove(10, &int_tree);
  int_tree.print();
  printf("\n");

  // --------------------------------------------
  CRT("Real BSTree");
  BSTree<float> float_tree;
  fill(20, &float_tree);
  float_tree.print();
  printf("\n");

  fill(5, &float_tree);
  float_tree.print();
  printf("\n");

  remove(10, &float_tree);
  float_tree.print();
  printf("\n");

  // --------------------------------------------
  CRT("String BSTree");
  BSTree<std::string> str_tree;
  fill(20, &str_tree);
  str_tree.print();
  printf("\n");

  fill(5, &str_tree);
  str_tree.print();
  printf("\n");

  remove(20, &str_tree);
  str_tree.print();
  printf("\n");

  DBG("[Lesson 4]: Class templates 1 [END]");
  return 0;
}

