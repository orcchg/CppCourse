#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include "logger.h"

#define SIZE 10

// @see http://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls
// @more https://gist.github.com/jeetsukumaran/307264

/* Linked list */
// ----------------------------------------------------------------------------
template <typename T>
struct Node {
  T data;
  Node* next;

  Node(T value);
  ~Node();

  Node<T>& operator = (Node<T> rhs);
};

template <typename T>
class LinkedList {
public:
  LinkedList();
  ~LinkedList();
  void push_back(T value);

  inline size_t getSize() const { return m_size; }

  /* Inner iterator */
  // --------------------------------------------
  class Iterator {
  public:
    // member-functions
    Iterator(Node<T>* ptr) : m_ptr(ptr) {}

    Iterator& operator ++ () {
      m_ptr = m_ptr->next;
      return *this;
    }

    Iterator operator ++ (int) {
      Iterator old_it = *this;  // copy pointer value
      ++(*this);
      return old_it;
    }

    bool operator == (const Iterator& rhs) const { return m_ptr == rhs.m_ptr; }
    bool operator != (const Iterator& rhs) const { return m_ptr != rhs.m_ptr; }

    Node<T>& operator * () { return *m_ptr; }
    Node<T>* operator -> () { return m_ptr; }

  private:
    Node<T>* m_ptr;
  };
  // --------------------------------------------

  Iterator begin();
  Iterator end();

private:
  size_t m_size;
  Node<T>* m_head;
};

/* Iterator traits */
// ----------------------------------------------
// @see http://stackoverflow.com/questions/7927764/specializing-iterator-traits

namespace std {

template <typename T>
struct iterator_traits<typename LinkedList<T>::Iterator> {
  typedef Node<T> value_type;
  typedef Node<T>& reference;
  typedef Node<T>* pointer;
  typedef std::forward_iterator_tag iterator_category;
  typedef int difference_type;
};

}

/* Implementation */
// ----------------------------------------------------------------------------
template <typename T>
Node<T>::Node(T value) {
  data = value;
  next = nullptr;
}

template <typename T>
Node<T>::~Node() {
  next = nullptr;
}

template <typename T>
Node<T>& Node<T>::operator = (Node<T> rhs) {
  std::swap(data, rhs.data);
  std::swap(next, rhs.next);
  return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const Node<T>& node) {
  out << "(" << node.data << ")";
  return out;
}

/* Linked list */
// ----------------------------------------------
template <typename T>
LinkedList<T>::LinkedList()
  : m_size(0), m_head(nullptr) {
}

template <typename T>
LinkedList<T>::~LinkedList() {
  Node<T>* node = m_head;
  while (node != nullptr) {
    Node<T>* temporary = node;
    node = node->next;
    delete temporary;
    temporary = nullptr;
  }
}

template <typename T>
void LinkedList<T>::push_back(T value) {
  if (m_head == nullptr) {
    m_head = new Node<T>(value);
    m_size = 1;
  } else {
    Node<T>* node = m_head->next;
    Node<T>* prev = m_head;
    while (node != nullptr) {
      node = node->next;
      prev = prev->next;
    }
    node = new Node<T>(value);
    prev->next = node;
    ++m_size;
  }
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
  return Iterator(m_head);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
  Node<T>* node = m_head;
  while (node != nullptr) {  // Quiz: could it to be optimized ?
    node = node->next;
  }
  return Iterator(node);
}

/* Advance iterator */
// ----------------------------------------------------------------------------
template <typename Iterator, typename Tag>
void advanceIterator_inner(Iterator& iterator, size_t shift, Tag tag) {
  while (shift > 0) {
    ++iterator;
    --shift;
  }
}

/* Template specialization */
// ----------------------------------------------------------------------------
template <typename Iterator>
void advanceIterator_inner(Iterator& iterator, size_t shift, std::random_access_iterator_tag tag) {
  iterator += shift;
}

/* Iterator traits */
// ----------------------------------------------------------------------------
template <typename Iterator>
void advanceIterator(Iterator& iterator, size_t shift) {
  // deduce iterator tag from iterator's type
  typename std::iterator_traits<Iterator>::iterator_category tag;

  advanceIterator_inner(iterator, shift, tag);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 6]: Iterators 7");

  LinkedList<int> numbers;
  numbers.push_back(5);
  numbers.push_back(1);
  numbers.push_back(-4);
  numbers.push_back(2);
  numbers.push_back(-7);
  numbers.push_back(3);
  numbers.push_back(9);
  numbers.push_back(0);
  std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<Node<int>>(std::cout, " -> "));
  std::cout << std::endl;

  auto iterator = numbers.begin();

  advanceIterator(iterator, 5);
  INF("Shifted iterator: %i", iterator->data);

  DBG("[Lesson 6]: Iterators 7 [END]");
  return 0;
}

