#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "logger.h"

void print(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end) {
  std::copy(begin, end, std::ostream_iterator<int>(std::cout, " "));
  printf("\n");
}

/* Linked list */
// ----------------------------------------------------------------------------
struct Node {
  int data;
  Node* next;

  void init(int value);
  void destroy();
};

struct SortedLinkedList {
  Node* head;

  void init();
  void destroy();
  void add(int value);
  void print();
};

/* Implementation */
// ----------------------------------------------
void Node::init(int value) {
  data = value;
  next = nullptr;
}

void Node::destroy() {
  next = nullptr;
}

void SortedLinkedList::init() {
  head = nullptr;
}

void SortedLinkedList::destroy() {
  Node* node = head;
  while (node != nullptr) {
    Node* temporary = node;
    node = node->next;
    temporary->destroy();
    delete temporary;
    temporary = nullptr;
  }
}

void SortedLinkedList::add(int value) {
  if (head == nullptr) {
    head = new Node();
    head->init(value);
  } else {
    if (value < head->data) {
      Node* new_head = new Node();
      new_head->init(value);
      new_head->next = head;
      head = new_head;
    } else {
      Node* node = head->next;
      Node* prev = head;
      while (node != nullptr) {
        if (value < node->data) {
          Node* new_node = new Node();
          new_node->init(value);
          prev->next = new_node;
          new_node->next = node;
          return;
        }
        node = node->next;
        prev = prev->next;
      }
      node = new Node();
      node->init(value);
      prev->next = node;
    }
  }
}

void SortedLinkedList::print() {
  Node* node = head;
  while (node != nullptr) {
    printf("%i ", node->data);
    node = node->next;
  }
  printf("\n");
}

/* Main */
// ----------------------------------------------------------------------------
void performanceTest() {
  clock_t start = clock();
  clock_t elapsed = start;
  double min_ratio = 99999.9, max_ratio = 0;
  int size_at_min_ratio = 0, size_at_max_ratio = 0;

  while ((elapsed - start) < 5 * CLOCKS_PER_SEC) {
    int size = rand() % 10000 + 1000;

    std::vector<int> array;
    array.reserve(size);

    SortedLinkedList list;
    list.init();

    for (int i = 0; i < size; ++i) {
      int value = rand() % 1000;
      array.push_back(value);
    }

    clock_t sort_start = clock();
    for (int i = 0; i < size; ++i) {
      list.add(array[i]);
    }
    clock_t list_sort_elapsed = clock();
    std::sort(array.begin(), array.end());
    clock_t array_sort_elapsed = clock();

    list.destroy();

    double array_time = static_cast<double>(array_sort_elapsed - list_sort_elapsed) / CLOCKS_PER_SEC;
    double list_time = static_cast<double>(list_sort_elapsed - sort_start) / CLOCKS_PER_SEC;
    double ratio = list_time / array_time;
    INF("SORT size [%i]: array [%.8lf], list [%.8lf], ratio [%.8lf]", size, array_time, list_time, ratio);

    if (ratio > max_ratio) {
      max_ratio = ratio;
      size_at_max_ratio = size;
    }
    if (ratio < min_ratio) {
      min_ratio = ratio;
      size_at_min_ratio = size;
    }

    elapsed = clock();
  }
  WRN("Max ratio list / array [%.8lf] at size [%i]", max_ratio, size_at_max_ratio);
  DBG("Min ratio list / array [%.8lf] at size [%i]", min_ratio, size_at_min_ratio);
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays: Solutions 7");
  performanceTest();
  DBG("[Lesson 1]: Arrays: Solutions 7 [END]");
  return 0;
}

