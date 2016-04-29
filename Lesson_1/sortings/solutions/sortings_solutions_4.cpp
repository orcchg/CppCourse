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
  if (p < r) {
    size_t q = partition(array, p, r);
    quicksort(array, p, q);
    quicksort(array, q + 1, r);
  }
}

void quicksort(int array[], size_t size) {
  quicksort(array, 0, size);
}

namespace randomized {

size_t randomizedPartition(int array[], size_t p, size_t r) {
  size_t index = rand() % (r - p) + p;
  std::swap(array[index], array[r - 1]);
  return partition(array, p, r);
}

void quicksort(int array[], size_t p, size_t r) {
  if (p < r) {
    size_t q = randomizedPartition(array, p, r);
    quicksort(array, p, q);
    quicksort(array, q + 1, r);
  }
}

void quicksort(int array[], size_t size) {
  quicksort(array, 0, size);
}

}  // end namespace randomized

namespace tail {

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

}  // end namespace tail

}  // end namespace sort

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
  WRN("Unit test start");
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
    sort::randomized::quicksort(B, size);
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
  WRN("Unit test end");
}

/* Performance test */
// ----------------------------------------------
void performanceTest() {
  WRN("Performance test start");
  clock_t start = clock();
  clock_t elapsed = start;

  while ((elapsed - start) < 10 * CLOCKS_PER_SEC) {
    size_t size = std::rand() % 65536 + 1000;
    int* A = new int[size];
    int* B = new int[size];
    int* C = new int[size];

    generateArray(A, size);
    copy(A, B, size);
    copy(A, C, size);

    clock_t sort_start = clock();
    sort::quicksort(A, size);
    clock_t quicksort_elapsed = clock();
    sort::randomized::quicksort(B, size);
    clock_t randomized_quicksort_elapsed = clock();
    sort::tail::quicksort(C, size);
    clock_t tail_quicksort_elapsed = clock();

    double quicksort_time = static_cast<double>(quicksort_elapsed - sort_start) / CLOCKS_PER_SEC;
    double rand_quicksort_time = static_cast<double>(randomized_quicksort_elapsed - quicksort_elapsed) / CLOCKS_PER_SEC;
    double tail_quicksort_time = static_cast<double>(tail_quicksort_elapsed - randomized_quicksort_elapsed) / CLOCKS_PER_SEC;

    INF("SORT: size [%zu], quick [%.8lf], rand [%.8lf], tail [%.8lf]", size, quicksort_time, rand_quicksort_time, tail_quicksort_time);

    delete [] A;
    delete [] B;
    delete [] C;

    elapsed = clock();
  }
  WRN("Performance test end");
}

/* Main */
//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Solutions 4");
  unitTest();
  performanceTest();
  DBG("[Lesson 1]: Sortings: Solutions 4 [END]");
  return 0;
}

