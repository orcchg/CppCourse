#include <algorithm>
#include <iostream>
#include "logger.h"

class Vector {
public:
  Vector(size_t size, int array[]);
  Vector(const Vector& obj);
  ~Vector();

  size_t getSize() const { return m_size; }
  int operator [](size_t index) const { return m_data[index]; }

  Vector& operator = (const Vector& rhs);

private:
  size_t m_size;
  int* m_data;
};

Vector::Vector(size_t size, int array[])
  : m_size(size)
  , m_data(new int[size]) {
  INF("Constructor");
  std::copy(array, array + size, m_data);
}

Vector::Vector(const Vector& obj)
  : m_size(obj.m_size)
  , m_data(new int[obj.m_size]) {
  CRT("Copy constructor");
  std::copy(obj.m_data, obj.m_data + obj.m_size, m_data);
}

Vector::~Vector() {
  INF("~Destructor");
  delete [] m_data;
  m_data = nullptr;
}

Vector& Vector::operator = (const Vector& rhs) {  // Copy & Swap idiom
  Vector temporary = rhs;  // Quiz: what operation here ?
  std::swap(m_size, temporary.m_size);
  std::swap(m_data, temporary.m_data);
  return *this;
}

std::ostream& operator << (std::ostream& out, const Vector& vector) {
  out << "{ ";
  for (size_t i = 0; i < vector.getSize(); ++i) {
    out << vector[i] << " ";
  }
  out << "}";
  return out;
}

int main(int argc, char** argv) {
  DBG("[Lesson 3]: Class 6.3.2");

  int array_one[10] = {5, 7, -3, 4, 15, 2, 0, -8, 9, 1};
  int array_two[15] = {5, -1, 4, 2, 11, 2, 12, 7, -8, 6, -3, -4, 5, 0, 2};

  Vector first(10, array_one);
  std::cout << "First: " << first << std::endl;

  Vector second(15, array_two);
  std::cout << "Second: " << second << std::endl;

  INF("Self assignment");
  second = second;  // self assignment
  std::cout << "Second Self: " << second << std::endl;

  INF("After assignment");
  second = first;
  std::cout << "Second: " << second << std::endl;

  DBG("[Lesson 3]: Class 6.3.2 [END]");
  return 0;
}

