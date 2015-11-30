#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "bst.h"
#include "logger.h"

void fillInt(size_t size, BSTree<int>* bst) {
  INF("Inserting into BSTree...");
  for (size_t i = 0; i < size; ++i) {
    int value = rand() % 100;
    printf("\e[5;00;36m%i \e[m", value);
    bst->insert(value);
  }
  printf("\n");
}

void removeInt(size_t size, BSTree<int>* bst) {
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

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Class templates 0");

  BSTree<int> int_tree;
  fillInt(20, &int_tree);
  int_tree.print();
  printf("\n");

  fillInt(5, &int_tree);
  int_tree.print();
  printf("\n");

  removeInt(10, &int_tree);
  int_tree.print();
  printf("\n");

  DBG("[Lesson 4]: Class templates 0 [END]");
  return 0;
}

