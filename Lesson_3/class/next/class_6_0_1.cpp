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
  int& operator [](size_t index) { return m_data[index]; }

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
  , m_data(obj.m_data) {
  CRT("Copy constructor");
}

Vector::~Vector() {
  INF("~Destructor");
  delete [] m_data;
  m_data = nullptr;
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
  DBG("[Lesson 3]: Class 6.0.1");

  int array[10] = {5, 7, -3, 4, 15, 2, 0, -8, 9, 1};

  Vector first(10, array);
  std::cout << "First: " << first << std::endl;

  {
    DBG("Enter block 1");
    Vector second(first);
    second[5] = 0;
    second[6] = 1;
    second[7] = 2;
    second[8] = 3;
    second[9] = 4;
    std::cout << "Second: " << second << std::endl;
    DBG("Exit block 1");
  }

  std::cout << "First again: " << first << std::endl;

  DBG("[Lesson 3]: Class 6.0.1 [END]");
  // crash
  return 0;
}

