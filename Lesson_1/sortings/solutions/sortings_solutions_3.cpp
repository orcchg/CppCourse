#include <algorithm>
#include <ctime>
#include "logger.h"

namespace sort {

size_t partition(int array[], size_t p, size_t r) {
  int pivot = array[r - 1];
  size_t i = p;

  for (size_t j = p + 1; j < r; ++j) {
    if (array[j - 1] <= pivot) {
      ++i;
      std::swap(array[i - 1], array[j - 1]);
    }
  }
  std::swap(array[i], array[r - 1]);
  return i;
}

void quicksort(int array[], size_t p, size_t r) {
  while (p < r) {
    size_t q = partition(array, p, r);
    if (q - p + 1 < r - q) {
      quicksort(array, p, q);
      p = q;
    } else {
      quicksort(array, q + 1, r);
      r = q;
    }
  }
}

void quicksort(int array[], size_t size) {
  quicksort(array, 0, size);
}

}

/* Utility */
// ----------------------------------------------------------------------------
void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

void copy(int source[], int destination[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    *destination++ = *source++;
  }
}

bool equal(int A[], int B[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (A[i] != B[i]) {
      return false;
    }
  }
  return true;
}

void generateArray(int array[], size_t size) {
  std::default_random_engine rng;
  std::uniform_int_distribution<int> distribution;

  for (size_t i = 0; i < size; ++i) {
    array[i] = distribution(rng);
  }
}

/* Unit test */
// ----------------------------------------------------------------------------
void unitTest() {
  clock_t start = clock();
  clock_t elapsed = start;
  bool flag = true;

  while (flag && (elapsed - start) < 10 * CLOCKS_PER_SEC) {
    size_t size = std::rand() % 65536 + 1000;
    int* A = new int[size];
    int* B = new int[size];

    generateArray(A, size);
    copy(A, B, size);

    std::sort(A, A + size);
    sort::quicksort(B, size);
    if (!equal(A, B, size)) {
      ERR("Arrays not equal after sorting!");
      flag = false;
    } else {
      INF("OK: %zu", size);
    }

    delete [] A;
    delete [] B;

    elapsed = clock();
  }
}

/* Main */
//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Solutions 3");
  unitTest();
  DBG("[Lesson 1]: Sortings: Solutions 3 [END]");
  return 0;
}

