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

struct LinkedList {
  Node* head;

  void init();
  void destroy();
  void push_back(int value);
  void print();
};

LinkedList list;  // global list

/* Implementation */
// ----------------------------------------------
void Node::init(int value) {
  data = value;
  next = nullptr;
}

void Node::destroy() {
  next = nullptr;
}

void LinkedList::init() {
  head = nullptr;
}

void LinkedList::destroy() {
  Node* node = head;
  while (node != nullptr) {
    Node* temporary = node;
    node = node->next;
    temporary->destroy();
    delete temporary;
    temporary = nullptr;
  }
}

void LinkedList::push_back(int value) {
  if (head == nullptr) {
    head = new Node();
    head->init(value);
  } else {
    Node* node = head->next;
    Node* prev = head;
    while (node != nullptr) {
      node = node->next;
      prev = prev->next;
    }
    node = new Node();
    node->init(value);
    prev->next = node;
  }
}

void LinkedList::print() {
  Node* node = head;
  while (node != nullptr) {
    printf("%i ", node->data);
    node = node->next;
  }
  printf("\n");
}

/* Interface */
// ----------------------------------------------------------------------------
const char* PUSH = "push";
const char* PRINT = "print";
const char* EXIT = "exit";

int readValue() {
  int value = 0;
  printf("value = ");
  scanf("%i", &value);
  return value;
}

bool evaluate(char* command) {
  if (strcmp(PUSH, command) == 0) {
    list.push_back(readValue());
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
  DBG("[Lesson 1]: Arrays 14");

  list.init();

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  list.destroy();

  DBG("[Lesson 1]: Arrays 14 [END]");
  return 0;
}

