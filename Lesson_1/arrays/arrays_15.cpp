#include <cstdio>
#include <cstring>
#include "logger.h"

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

SortedLinkedList list;  // global list

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

/* Interface */
// ----------------------------------------------------------------------------
const char* ADD = "add";
const char* PRINT = "print";
const char* EXIT = "exit";

int readValue() {
  int value = 0;
  printf("value = ");
  scanf("%i", &value);
  return value;
}

bool evaluate(char* command) {
  if (strcmp(ADD, command) == 0) {
    list.add(readValue());
  } else if (strcmp(PRINT, command) == 0) {
    list.print();
  } else if (strcmp(EXIT, command) == 0) {
    return false;
  } else {
    WRN("Undefined command: %s", command);
  }
  return true;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays 15");

  list.init();

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  list.destroy();

  DBG("[Lesson 1]: Arrays 15 [END]");
  return 0;
}

