#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "logger.h"

/* Template array container */
/**
 * Implementation should not rely on assignment
 * operator of type T or it's default ctor.
 */
template <class T>
class Array {
public:
  Array(size_t capacity);
  Array(const Array& obj);
  ~Array();

  Array& operator = (const Array& rhs);
  T& operator [] (size_t index);
  const T& operator [] (size_t index) const;

  void swap(Array& rhs);
  void push_back(const T& item);

  size_t size() const;
  size_t capacity() const;

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

private:
  T* m_begin;
  T* m_end;
  T* m_reserved;
};

template <class T>
size_t Array<T>::size() const {
  return m_end - m_begin;
}

template <class T>
size_t Array<T>::capacity() const {
  return m_reserved - m_begin;
}

template <class T>
T* Array<T>::begin() {
  return m_begin;
}

template <class T>
T* Array<T>::end() {
  return m_end;
}

template <class T>
const T* Array<T>::begin() const {
  return m_begin;
}

template <class T>
const T* Array<T>::end() const {
  return m_end;
}

template <class T>
std::ostream& operator << (std::ostream& out, const Array<T>& obj) {
  for (const T* it = obj.begin(); it != obj.end(); ++it) {
    out << *it << " ";
  }
  return out;
}

/* Implementation */
// ----------------------------------------------
template <class T>
Array<T>::Array(size_t capacity)
  : m_begin(static_cast<T*>(malloc(sizeof(T) * capacity)))
  , m_end(m_begin)
  , m_reserved(m_begin + capacity) {
}

template <class T>
Array<T>::Array(const Array<T>& obj)
  : m_begin(static_cast<T*>(malloc(sizeof(T) * obj.capacity())))
  , m_end(m_begin)
  , m_reserved(m_begin + obj.capacity()) {
  // deep copy
  char* pointer = reinterpret_cast<char*>(m_begin);
  for (size_t i = 0; i < obj.size(); ++i, ++m_end, pointer += sizeof(T)) {
    m_end = new (pointer) T(obj[i]);
  }
}

template <class T>
Array<T>::~Array() {
  while (m_begin != m_end) {
    m_end->~T();
    --m_end;
  }
  free(m_begin);
}

// ----------------------------------------------
template <class T>
Array<T>& Array<T>::operator = (const Array<T>& rhs) {
  Array<T> temp = rhs;  // deep copy
  swap(*this, temp);
  return *this;
}

template <class T>
T& Array<T>::operator [] (size_t index) {
  return *(m_begin + index);
}

template <class T>
const T& Array<T>::operator [] (size_t index) const {
  return *(m_begin + index);
}

// ----------------------------------------------
template <class T>
void Array<T>::swap(Array<T>& rhs) {
  std::swap(m_begin, rhs.m_begin);
  std::swap(m_end, rhs.m_end);
  std::swap(m_reserved, rhs.m_reserved);
}

template <class T>
void Array<T>::push_back(const T& item) {
  char* pointer = reinterpret_cast<char*>(m_end);
  m_end = new (pointer) T(item);
  ++m_end;
}

/* Main */
// ------------------------------------------------------------------------------------------------
/**
 * Leak checking:
 * 
 * valgrind --leak-check=full --track-origins=yes ./a.out
 */
int main(int argc, char** argv) {
  DBG("[Lesson 4]: Class templates 2");

  Array<int> source(10);
  source.push_back(0);
  source.push_back(1);
  source.push_back(2);
  source.push_back(3);
  source.push_back(4);
  source.push_back(5);
  std::cout << source << std::endl;

  Array<int> copy = source;
  copy.push_back(6);
  copy.push_back(7);
  copy.push_back(8);
  std::cout << source << std::endl;
  std::cout << copy << std::endl;

  DBG("[Lesson 4]: Class templates 2 [END]");
  return 0;
}

