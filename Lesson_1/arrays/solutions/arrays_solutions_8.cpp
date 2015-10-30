#include <cstdio>
#include <cstring>
#include "logger.h"

/* Dobule Linked list */
// ----------------------------------------------------------------------------
struct Node {
  int data;
  Node* next;
  Node* prev;

  void init(int value);
  void destroy();
};

struct DoubleLinkedList {
  Node* head;

  void init();
  void destroy();
  void push_back(int value);
  void push_front(int value);
  void print();
};

DoubleLinkedList list;  // global list

/* Implementation */
// ----------------------------------------------
void Node::init(int value) {
  data = value;
  next = nullptr;
  prev = nullptr;
}

void Node::destroy() {
  next = nullptr;
  prev = nullptr;
}

void DoubleLinkedList::init() {
  head = nullptr;
}

void DoubleLinkedList::destroy() {
  Node* node = head;
  while (node != nullptr) {
    Node* temporary = node;
    node = node->next;
    temporary->destroy();
    delete temporary;
    temporary = nullptr;
  }
}

void DoubleLinkedList::push_back(int value) {
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
    node->prev = prev;
  }
}

void DoubleLinkedList::push_front(int value) {
  if (head == nullptr) {
    head = new Node();
    head->init(value);
  } else {
    Node* node = head->prev;
    Node* prev = head;
    while (node != nullptr) {
      node = node->prev;
      prev = prev->prev;
    }
    node = new Node();
    node->init(value);
    prev->prev = node;
    node->next = prev;
    head = node;
  }
}

void DoubleLinkedList::print() {
  Node* node = head;
  while (node != nullptr) {
    printf("%i ", node->data);
    node = node->next;
  }
  printf("\n");
}

/* Interface */
// ----------------------------------------------------------------------------
const char* BACK = "back";
const char* FRONT = "front";
const char* PRINT = "print";
const char* EXIT = "exit";

int readValue() {
  int value = 0;
  printf("value = ");
  scanf("%i", &value);
  return value;
}

bool evaluate(char* command) {
  if (strcmp(BACK, command) == 0) {
    list.push_back(readValue());
  } else if (strcmp(FRONT, command) == 0) {
    list.push_front(readValue());
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
  DBG("[Lesson 1]: Arrays: Solutions 8");

  list.init();

  char command[5];
  do {
    scanf("%s", command);
  } while (evaluate(command));

  list.destroy();

  DBG("[Lesson 1]: Arrays: Solutions 8 [END]");
  return 0;
}

