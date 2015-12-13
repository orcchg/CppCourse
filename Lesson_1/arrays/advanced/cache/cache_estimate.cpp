#include <cstdio>
#include <ctime>
#include "logger.h"

const long MBYTE = 1024 * 512;
const long CACHE_SIZE = 32 * MBYTE;
const long OFFSET = 4 * MBYTE;

/* CPU cycle count */
// ----------------------------------------------------------------------------
#include <stdint.h>

//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t rdtsc(){
  return __rdtsc();
}

//  Linux/GCC
#else

uint64_t rdtsc(){
  unsigned int lo,hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}

#endif

// ----------------------------------------------------------------------------
struct Node {
  int key;
  int value;  // index of next
};

void readNode(const Node& node) {
  // printf("Node {%i, %i}\n", node.key, node.value);
  int a = 5 + 7;
}

class BigArray {
public:
  BigArray(uint64_t size);
  ~BigArray();

  Node getNode(int fragment, int index) const;

private:
  uint64_t m_size;
  Node* m_array;
};

BigArray::BigArray(uint64_t size)
  : m_size(size)
  , m_array(new Node[size]) {
  for (long i = 0; i < size; ++i) {
    Node node;
    node.key = i;
    node.value = i + 1;
    m_array[i] = node;
  }
  m_array[size - 1].value = 0;
}

BigArray::~BigArray() {
  delete [] m_array;
  m_array = nullptr;
}

Node BigArray::getNode(int fragment, int index) const {
  return m_array[index + fragment * OFFSET];
}

// ----------------------------------------------
uint64_t walk(int N) {
  const long FRAGMENT_SIZE = CACHE_SIZE / N;
  BigArray bigArray(OFFSET * N * 10);
  uint64_t average = 0;

  for (int i = 0; i < FRAGMENT_SIZE; ++i) {
    for (int fragment = 0; fragment < N; ++fragment) {
      uint64_t start = rdtsc();
      readNode(bigArray.getNode(fragment, i));
      uint64_t elapsed = rdtsc() - start;
      // printf("%lu\n", elapsed);
      average += elapsed;
    }
  }
  average /= CACHE_SIZE;
  return average;
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays : Cache 2");

  for (int i = 1; i <= 32; ++i) {
    uint64_t average = walk(i);
    INF("Fragments: %i, Average time: %lu", i, average);
  }

  DBG("[Lesson 1]: Arrays : Cache 2 [END]");
  return 0;
}

