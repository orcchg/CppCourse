#include <algorithm>
#include <iostream>
#include "logger.h"

class Vector {
public:
  Vector();  // default constructor
  Vector(size_t size, int array[]);
  Vector(const Vector& obj);
  ~Vector();

  size_t getSize() const { return m_size; }
  int operator [](size_t index) const { return m_data[index]; }
  int& operator [](size_t index) { return m_data[index]; }

  Vector& operator = (Vector rhs);

private:
  size_t m_size;
  int* m_data;
};

Vector::Vector()
  : m_size(0)
  , m_data(nullptr) {
  INF("Default constructor");
}

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

Vector& Vector::operator = (Vector rhs) {  // Copy & Swap idiom
  WRN("Assigment Operator");
  std::swap(m_size, rhs.m_size);
  std::swap(m_data, rhs.m_data);
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
  DBG("[Lesson 3]: Class 6.4");

  int array_one[10] = {5, 7, -3, 4, 15, 2, 0, -8, 9, 1};
  int array_two[15] = {5, -1, 4, 2, 11, 2, 12, 7, -8, 6, -3, -4, 5, 0, 2};

  Vector vector;  // default constructor
  std::cout << "Init: " << vector << std::endl;

  for (size_t i = 0; i < 10; ++i) {
    vector[i] = array_one[i];
  }
  std::cout << "First: " << vector << std::endl;

  vector = Vector(15, array_two);
  std::cout << "Second: " << vector << std::endl;

  DBG("[Lesson 3]: Class 6.4 [END]");
  return 0;
}

