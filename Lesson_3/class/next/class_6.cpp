#include <algorithm>
#include <iostream>
#include "logger.h"

class Vector {
public:
  Vector(size_t size, int array[]);
  ~Vector();

  size_t getSize() const { return m_size; }
  int operator [](size_t index) const { return m_data[index]; }

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
  DBG("[Lesson 3]: Class 6");

  int array[10] = {5, 7, -3, 4, 15, 2, 0, -8, 9, 1};

  {
    DBG("Enter block 1");
    Vector vector(10, array);
    std::cout << vector << std::endl;
    DBG("Exit block 1");
  }

  DBG("[Lesson 3]: Class 6 [END]");
  return 0;
}

